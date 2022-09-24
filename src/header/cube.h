/*
cube.h

Definitions of the game board of 3 dimensional 4 in a row.
*/

#pragma once

#include "ball.h"
#include "util/error.h"
#include "util/util.h"

namespace blinear
{
    enum Coordinate : int
    {
        COORERR = -1,
        COOR1 = 0,
        COOR2,
        COOR3,
        COOR4,
    };

    ENABLE_BASE_OPERATORS_ON(Coordinate);

    struct Square
    {
        Coordinate x;
        Coordinate y;
        Coordinate z;
    };

    const Square SQUAREERR = Square{COORERR, COORERR, COORERR};

    struct Position
    {
        Coordinate x;
        Coordinate y;
    };

    const Position POSITIONERR = Position{COORERR, COORERR};

    bool IsError(Square);
    bool IsError(Position);
    Square IndexToSquare(int);
    int SquareToIndex(Square);

    /*
    The game board of 3 dimensional 4 in a row.
    */
    class Cube
    {
    private:
        Ball squares[64];
        Ball turn;

    public:
        Cube() : turn(WHITE)
        {
            for (int i = 0; i < 64; i++)
            {
                squares[i] = NOBALL;
            }
        };

        Ball GetSquare(Square);
        BLError SetSquare(Square, Ball);
    };
}