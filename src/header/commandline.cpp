#include "commandline.h"

#include <iostream>

namespace blinear
{
    BLError CommandLine::DisplayCube(Cube *cube)
    {
        Ball b;
        std::string b_str, step_str;
        std::cout << std::endl;
        if (setting.displaySpendTurn)
        {
            std::cout << "turn " << (cube->GetSpendTurn() + 1) << std::endl
                      << std::endl;
        }
        for (Coordinate z = COOR4; z >= COOR1; z--)
        {
            switch (z)
            {
            case COOR1:
                step_str = "1st";
                break;
            case COOR2:
                step_str = "2nd";
                break;
            case COOR3:
                step_str = "3rd";
                break;
            case COOR4:
                step_str = "4th";
                break;
            default:
                break;
            }
            std::cout << step_str << " step" << std::endl;
            for (Coordinate y = COOR4; y >= COOR1; y--)
            {
                std::cout << " | ";
                for (Coordinate x = COOR1; x <= COOR4; x++)
                {
                    b = cube->GetSquare(Square{x, y, z});
                    switch (b)
                    {
                    case WHITE:
                        b_str = "w";
                        break;
                    case BLACK:
                        b_str = "b";
                        break;
                    case NOBALL:
                        b_str = "-";
                    }
                    std::cout << b_str << " ";
                }
                std::cout << std::endl;
            }
        }
        if (setting.displayEvaluation)
        {
            std::cout << "evaluation : " << computer->GetEvaluation() << std::endl;
        }
        if (setting.displayBestMoves)
        {
            std::cout << "BestMove : " << PositionToString(computer->GetBestMove(0)) << std::endl;
        }
        std::cout << ((cube->GetTurn() == WHITE) ? "White" : "Black") << " turn" << std::endl;

        std::cout << std::endl;

        return blet::NoErr;
    }

    BLError CommandLine::PlayGameParser(Cube *cube, std::string command, std::string *result)
    {
        *result = "";

        std::string com;
        Position record[64], bestmove;
        int i, j, number, temp;
        int phaze;
        bool dicided;
        bool mode_move = false;
        bool mode_move_back = false;
        bool mode_get = false;
        bool mode_get_bestMoves = false;

        i = 0;
        phaze = 1;
        for (char c : command)
        {
            i++;
            if (c != ' ')
            {
                com += c;
                if (i != command.length())
                    continue;
            }

            switch (phaze)
            {
            case 1:
                if (com == "move")
                    mode_move = true;
                else if (com == "get")
                    mode_get = true;
                else if (com == "exit")
                {
                    *result = "#exit";
                    return blet::NoErr;
                }
                else
                    return blet::GenCommandParseError("invalid command : " + com);
                break;
            case 2:
                if (mode_move)
                {
                    if (com == "back")
                    {
                        number = 1;
                        mode_move_back = true;
                    }
                    else if ((com.length() == 2) ? ('1' <= com[0] && com[0] <= '4' && '1' <= com[1] && com[1] <= '4') : false)
                    {
                        cube->Move(StringToPosition(com));
                        return blet::NoErr;
                    }
                    else
                    {
                        return blet::GenCommandParseError("invalid argument : " + com);
                    }
                }
                else if (mode_get)
                {
                    if (com == "spendTurn")
                    {
                        *result = std::to_string(cube->GetSpendTurn());
                    }
                    else if (com == "turn")
                    {
                        *result = std::to_string(cube->GetTurn());
                    }
                    else if (com == "bestMoves")
                    {
                        number = 1;
                        mode_get_bestMoves = true;
                    }
                    else if (com == "record")
                    {
                        cube->GetRecord(record);
                        for (int i = 0; i < 64; i++)
                        {
                            if (IsError(record[i]))
                                break;

                            *result += std::to_string(i + 1) + ". " + PositionToString(record[i]);

                            if (i % 2 == 0)
                                *result += " ";
                            else
                                *result += "\n";
                        }
                    }
                    else
                    {
                        return blet::GenCommandParseError("invalid argument : " + com);
                    }
                }
                else
                {
                    return blet::GenCommandParseError("too many arguments");
                }
                break;
            case 3:
                if (mode_move_back || mode_get_bestMoves)
                {
                    number = 0;
                    for (char c : com)
                    {
                        if (c < '0' || '9' < c)
                            return blet::GenCommandParseError("integer required : " + com);

                        number *= 10;
                        number += c - '0';
                    }
                }
                else
                {
                    return blet::GenCommandParseError("too many arguments");
                }
                break;
            default:
                return blet::GenCommandParseError("too many arguments");
            }

            com = "";
            phaze++;
        }

        if (mode_move_back)
        {
            for (j = 0; j < number; j++)
            {
                if (cube->MoveBack() != blet::NoErr)
                {
                    *result = "Warning : more than the number of spent turns : " + std::to_string(number);
                    break;
                }
            }
        }
        else if (mode_get_bestMoves)
        {
            for (j = 0; j < number; j++)
            {
                if (IsError(bestmove = computer->GetBestMove(j)))
                {
                    *result += "\nNote : not analyzed after this move";
                    break;
                }

                *result += std::to_string(cube->GetSpendTurn() + j + 1) + ". " + PositionToString(bestmove);

                if (j % 2 == 0)
                    *result += " ";
                else
                    *result += "\n";
            }
        }

        return blet::NoErr;
    }

    void CommandLine::PlayGamePvP()
    {
        Cube c;
        std::string com, res;
        BLError err;
        int spent = -1;

        while (c.JudgeWinner() == NOBALL)
        {
            if (spent != c.GetSpendTurn())
            {
                spent = c.GetSpendTurn();
                computer->evaluate(c);
                DisplayCube(&c);
            }
            std::cout << "User > ";
            std::getline(std::cin, com);
            err = PlayGameParser(&c, com, &res);
            if (err != blet::NoErr)
                std::cout << err.ErrorMessage() << std::endl;
            if (res == "#exit")
                break;
            else if (res != "")
                std::cout << res << std::endl
                          << std::endl;
        }

        switch (c.JudgeWinner())
        {
        case WHITE:
            std::cout << "White wins" << std::endl
                      << std::endl;
            break;
        case BLACK:
            std::cout << "Black wins" << std::endl
                      << std::endl;
            break;
        case NOBALL:
            std::cout << "Drow" << std::endl
                      << std::endl;
        }
    }
}