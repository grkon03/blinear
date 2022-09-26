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

            if (c == WHITE)
                evl += (whiteParams[i] * count) / 4;
            else if (c == BLACK)
                evl -= (blackParams[i] * count) / 4;
        }

        return evl;
    }
}