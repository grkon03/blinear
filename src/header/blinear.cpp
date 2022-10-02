#include "blinear.h"
#include <iostream>
#include <fstream>

namespace blinear
{
    /*
    if the file is not exists, error will be returned.
    if filename == "", default file will be specified.
     */
    BLError Blinear::LoadParams(Ball color, std::string filename)
    {
        if (color == NOBALL)
            return blet::GenLoadParamError("color is NOBALL");

        if (filename == "")
        {
            filename = (color == WHITE) ? DEFAULT_WHITEPARAM_FILE : DEFAULT_BLACKPARAM_FILE;
        }

        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs)
            return blet::GenLoadParamError("fail to open the file");

        if (color == WHITE)
        {
            for (int i = 0; i < MAX_LINES; i++)
            {
                ifs.read((char *)&whiteParams[i], sizeof(double));
            }
        }
        else
        {
            for (int i = 0; i < MAX_LINES; i++)
            {
                ifs.read((char *)&blackParams[i], sizeof(double));
            }
        }

        ifs.close();

        return blet::NoErr;
    }

    /*
    if the file is not exists, error will be returned.
     */
    BLError Blinear::SaveParams(Ball color, std::string filename)
    {
        if (color == NOBALL)
            return blet::GenSaveParamError("color is NOBALL");

        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs)
            return blet::GenSaveParamError("the file doesn't exist");

        ifs.close();

        std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
        if (!ofs)
            return blet::GenSaveParamError("fail to open the file");

        if (color == WHITE)
        {
            for (int i = 0; i < MAX_LINES; i++)
            {
                ofs.write((char *)&whiteParams[i], sizeof(double));
            }
        }
        else
        {
            for (int i = 0; i < MAX_LINES; i++)
            {
                ofs.write((char *)&blackParams[i], sizeof(double));
            }
        }

        ofs.close();

        return blet::NoErr;
    }

    /*
    default parameter : ONELINE_WORTH
    */
    BLError Blinear::NewParamFile(std::string filename)
    {

        std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
        if (!ofs)
            return blet::GenNewParamFileError("fail to open the file");

        for (int i = 0; i < MAX_LINES; i++)
        {
            ofs.write((char *)&ONELINE_WORTH, sizeof(double));
        }

        ofs.close();

        return blet::NoErr;
    }

    /*
    default parameter : ONELINE_WORTH
    */
    BLError Blinear::NewParamFile(std::string filename, double params[MAX_LINES])
    {

        std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
        if (!ofs)
            return blet::GenNewParamFileError("fail to open the file");

        for (int i = 0; i < MAX_LINES; i++)
        {
            ofs.write((char *)&params[i], sizeof(double));
        }

        ofs.close();

        return blet::NoErr;
    }

    Position Blinear::GetBestMove(int index)
    {
        return bestMoves[index];
    }

    double Blinear::GetParam(Ball color, int index)
    {
        switch (color)
        {
        case WHITE:
            return whiteParams[index];
        case BLACK:
            return blackParams[index];
        case NOBALL:
            return -1;
        }

        return -1;
    }

    double Blinear::GetEvaluation() { return evaluation; }

    double Blinear::evaluateTemporary(Cube cube)
    {
        double evl = 0;
        Ball c = NOBALL, ctmp;
        int i, j, count;
        bool skip;

        for (i = 0; i < MAX_LINES; i++)
        {
            c = NOBALL;
            count = 0;
            skip = false;
            for (j = 0; j < 4; j++)
            {
                if (c == NOBALL)
                {
                    c = cube.GetSquare(DEFAULT_LINES[i][j]);
                }
                else
                {
                    ctmp = cube.GetSquare(DEFAULT_LINES[i][j]);
                    if (ctmp != NOBALL)
                    {
                        if (c == ctmp)
                            count++;
                        else
                        {
                            skip = true;
                            break;
                        }
                    }
                }
            }

            if (skip)
                continue;

            if (count == 4)
            {
                if (c == WHITE)
                    return 10000;
                else
                    return -10000;
            }

            if (c == WHITE)
                evl += (whiteParams[i] * count) / 4;
            else if (c == BLACK)
                evl -= (blackParams[i] * count) / 4;
        }

        return evl;
    }

    double Blinear::alphabeta(Cube cube, double alpha, double beta, int depth, int depthMax)
    {
        switch (cube.JudgeWinner())
        {
        case WHITE:
            return 10000;
        case BLACK:
            return -10000;
        default:
            break;
        }

        if (cube.GetSpendTurn() == 64)
        {
            bestMovesLength = depth;
            return 0;
        }

        Cube copy;
        double ret;
        BLError err;

        if (depth == depthMax)
        {
            return evaluateTemporary(cube);
        }
        else
        {
            for (Coordinate x = COOR1; x <= COOR4; x++)
            {
                for (Coordinate y = COOR1; y <= COOR4; y++)
                {
                    copy = cube;
                    err = copy.Move(Position{x, y});

                    if (err != blet::NoErr)
                        continue;

                    ret = alphabeta(copy, alpha, beta, depth + 1, depthMax);

                    switch (cube.GetTurn())
                    {
                    case WHITE:
                        if (beta <= ret)
                            return ret;
                        else if (alpha < ret)
                        {
                            alpha = ret;
                            bestMoves[depth] = Position{x, y};
                        }
                        break;
                    case BLACK:
                        if (alpha >= ret)
                            return ret;
                        else if (beta > ret)
                        {
                            beta = ret;
                            bestMoves[depth] = Position{x, y};
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        switch (cube.GetTurn())
        {
        case WHITE:
            return alpha;
        case BLACK:
            return beta;
        default:
            break;
        }

        return 0;
    }

    double Blinear::evaluate(Cube cube)
    {
        analyzed = cube;
        bestMovesLength = 6;
        for (int i = 0; i < 64; i++)
        {
            bestMoves[i] = POSITIONERR;
        }
        evaluation = alphabeta(cube, -100000, 100000, 0, 6);
        return evaluation;
    }
}