#include "cube.h"

namespace blinear
{
    bool IsError(Square square)
    {
        if (
            square.x == COORERR ||
            square.y == COORERR ||
            square.z == COORERR)
        {
            return true;
        }

        return false;
    }

    Square IndexToSquare(int index)
    {
        if (index < 0 || 63 < index)
        {
            return SQUAREERR;
        }

        return Square{Coordinate(index / 16), Coordinate((index / 4) % 4), Coordinate(index % 4)};
    }

    int SquareToIndex(Square square)
    {
        if (IsError(square))
            return -1;
        return (square.x * 16 + square.y * 4 + square.z);
    }

    Ball Cube::GetSquare(Square square)
    {
        if (IsError(square))
            return NOBALL;
        return squares[SquareToIndex(square)];
    }

    BLError Cube::SetSquare(Square square, Ball b)
    {
        if (IsError(square))
            return blet::GenSetSquareError("the square is SQUAREERR");
        squares[SquareToIndex(square)] = b;
        return blet::NoErr;
    }
}