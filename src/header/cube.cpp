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

    bool IsError(Position pos)
    {
        if (
            pos.x == COORERR ||
            pos.y == COORERR)
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

    Square Line::operator[](int n)
    {
        if (n < 0 && 3 < n)
            return SQUAREERR;
        return Square{start.x + xdir * n, start.y + ydir * n, start.z + zdir * n};
    }

    BLError Line::SetLineByLineNumber(int num)
    {
        int num_s;
        if (num < 0)
        {
            return blet::GenSetLineError("This number has no specified line");
        }
        else if (num < 16)
        {
            num_s = num;
            start = Square{Coordinate(num_s / 4), Coordinate(num_s % 4), COOR1};
            xdir = NOTMOVE;
            ydir = NOTMOVE;
            zdir = PLUSDIR;
        }
        else if (num < 32)
        {
            num_s = num - 16;
            start = Square{Coordinate(num_s % 4), COOR1, Coordinate(num_s / 4)};
            xdir = NOTMOVE;
            ydir = PLUSDIR;
            zdir = NOTMOVE;
        }
        else if (num < 48)
        {
            num_s = num - 32;
            start = Square{COOR1, Coordinate(num_s / 4), Coordinate(num_s % 4)};
            xdir = PLUSDIR;
            ydir = NOTMOVE;
            zdir = NOTMOVE;
        }
        else if (num < 56)
        {
            num_s = (num - 48) / 2;
            xdir = NOTMOVE;
            ydir = PLUSDIR;
            if (num % 2 == 0)
            {
                start = Square{Coordinate(num_s), COOR1, COOR1};
                zdir = PLUSDIR;
            }
            else
            {
                start = Square{Coordinate(num_s), COOR1, COOR4};
                zdir = MINUSDIR;
            }
        }
        else if (num < 64)
        {
            num_s = (num - 56) / 2;
            xdir = PLUSDIR;
            ydir = NOTMOVE;
            if (num % 2 == 0)
            {
                start = Square{COOR1, Coordinate(num_s), COOR1};
                zdir = PLUSDIR;
            }
            else
            {
                start = Square{COOR1, Coordinate(num_s), COOR4};
                zdir = MINUSDIR;
            }
        }
        else if (num < 72)
        {
            num_s = (num - 64) / 2;
            xdir = PLUSDIR;
            zdir = NOTMOVE;
            if (num % 2 == 0)
            {
                start = Square{COOR1, COOR1, Coordinate(num_s)};
                ydir = PLUSDIR;
            }
            else
            {
                start = Square{COOR1, COOR4, Coordinate(num_s)};
                ydir = MINUSDIR;
            }
        }
        else if (num < 76)
        {
            num_s = (num - 72);
            start = Square{COOR1 + ((num_s / 2) % 2) * 3, COOR1 + ((num_s % 2) * 3), COOR1};
            xdir = Direction(PLUSDIR - ((num_s / 2) % 2) * 2);
            ydir = Direction(PLUSDIR - (num_s % 2) * 2);
            zdir = PLUSDIR;
        }
        else
        {
            return blet::GenSetLineError("This number has no specified line");
        }

        return blet::NoErr;
    }

    int Line::GetLineNumber()
    {
        if (xdir == NOTMOVE)
        {
            if (ydir == NOTMOVE)
            {
                if (zdir == PLUSDIR)
                {
                    return ((int)start.x * 4 + (int)start.y);
                }
            }
            else if (ydir == PLUSDIR)
            {
                if (zdir == NOTMOVE)
                {
                    return ((int)start.z * 4 + (int)start.x + 16);
                }
                else
                {
                    return ((int)start.x + 48 + (1 - (int)zdir) / 2);
                }
            }
        }
        else
        {
            if (ydir == NOTMOVE)
            {
                if (zdir == NOTMOVE)
                {
                    return ((int)start.y * 4 + (int)start.z + 32);
                }
                else
                {
                    return ((int)start.y + 56 + (1 - (int)zdir) / 2);
                }
            }
            else
            {
                if (zdir == NOTMOVE)
                {
                    return ((int)start.z + 64 + (1 - (int)ydir) / 2);
                }
                else
                {
                    return ((1 - (int)xdir) + (1 - (int)ydir) / 2);
                }
            }
        }

        return -1;
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

    BLError Cube::Move(Position pos)
    {
        if (IsError(pos))
            return blet::GenMoveError("this position is POSITIONERR");

        for (Coordinate c = COOR1; c <= COOR4; c++)
        {
            if (GetSquare(Square{pos.x, pos.y, c}) == NOBALL)
            {
                SetSquare(Square{pos.x, pos.y, c}, turn);
                turn++;
                return blet::NoErr;
            }
        }
        return blet::GenMoveError("this vertical row is full of balls");
    }
}