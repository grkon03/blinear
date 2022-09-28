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
        std::cout << ((cube->GetTurn() == WHITE) ? "White" : "Black") << " turn" << std::endl;
        std::cout << std::endl;

        return blet::NoErr;
    }
}