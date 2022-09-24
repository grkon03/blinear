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

    enum Direction : int
    {
        MINUSDIR = -1,
        NOTMOVE,
        PLUSDIR = 1,
    };

    /*
    Class of line of the board
    */
    class Line
    {
    private:
        Square start;
        Direction xdir;
        Direction ydir;
        Direction zdir;

    public:
        Line(Square s, Direction x, Direction y, Direction z) : start(s), xdir(x), ydir(y), zdir(z){};
        Line(int n) { SetLineByLineNumber(n); }

        Square operator[](int);
        Square operator[](int) const;
        BLError SetLineByLineNumber(int);
        int GetLineNumber();
    };

    constexpr int MAX_LINES = 76;

    extern const Line DEFAULT_LINES[MAX_LINES];

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
        BLError Move(Position);
        Ball JudgeWinner();
    };
}