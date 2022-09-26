#include "commandline.h"

#include <iostream>

namespace blinear
{
    BLError CommandLine::DisplayCube(Cube *cube)
    {
        Ball b;
        std::string b_str;
        std::cout << std::endl;
        if (setting.displaySpendTurn)
        {
            std::cout << (cube->GetSpendTurn() + 1) << "ターン目" << std::endl
                      << std::endl;
        }
        for (Coordinate z = COOR4; z >= COOR1; z--)
        {
            std::cout << ((int)z + 1) << "段目" << std::endl;
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
        std::cout << ((cube->GetTurn() == WHITE) ? "白" : "黒") << "のターンです" << std::endl;
        std::cout << std::endl;

        return blet::NoErr;
    }
}