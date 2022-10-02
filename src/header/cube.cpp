#include "cube.h"

namespace blinear
{
    const Line DEFAULT_LINES[MAX_LINES] = {
        Line(0), Line(1), Line(2), Line(3), Line(4), Line(5), Line(6), Line(7), Line(8), Line(9),
        Line(10), Line(11), Line(12), Line(13), Line(14), Line(15), Line(16), Line(17), Line(18), Line(19),
        Line(20), Line(21), Line(22), Line(23), Line(24), Line(25), Line(26), Line(27), Line(28), Line(29),
        Line(30), Line(31), Line(32), Line(33), Line(34), Line(35), Line(36), Line(37), Line(38), Line(39),
        Line(40), Line(41), Line(42), Line(43), Line(44), Line(45), Line(46), Line(47), Line(48), Line(49),
        Line(50), Line(51), Line(52), Line(53), Line(54), Line(55), Line(56), Line(57), Line(58), Line(59),
        Line(60), Line(61), Line(62), Line(63), Line(64), Line(65), Line(66), Line(67), Line(68), Line(69),
        Line(70), Line(71), Line(72), Line(73), Line(74), Line(75)};

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

    std::string PositionToString(Position pos)
    {
        if (IsError(pos))
            return "ER";
        return std::to_string(((int)pos.x + 1) * 10 + (int)pos.y + 1);
    }

    Position StringToPosition(std::string str)
    {
        if (str.length() != 2)
            return POSITIONERR;
        if (str[0] < '1' || '4' < str[0] || str[1] < '1' || '4' < str[1])
            return POSITIONERR;
        return Position{Coordinate(str[0] - '1'), Coordinate(str[1] - '1')};
    }

    Square Line::operator[](int n)
    {
        if (n < 0 && 3 < n)
            return SQUAREERR;
        return Square{start.x + xdir * n, start.y + ydir * n, start.z + zdir * n};
    }

    Square Line::operator[](int n) const
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
            start = Square{COOR1 + (int(num_s / 2) * 3), COOR1 + ((num_s % 2) * 3), COOR1};
            xdir = Direction(PLUSDIR - (int(num_s / 2) * 2));
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
                    return ((int)start.x * 2 + 48 + (1 - (int)zdir) / 2);
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
                    return ((int)start.y * 2 + 56 + (1 - (int)zdir) / 2);
                }
            }
            else
            {
                if (zdir == NOTMOVE)
                {
                    return ((int)start.z * 2 + 64 + (1 - (int)ydir) / 2);
                }
                else
                {
                    return ((1 - (int)xdir) + 72 + (1 - (int)ydir) / 2);
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
                record[spendTurn] = pos;
                turn++;
                spendTurn++;
                return blet::NoErr;
            }
        }
        return blet::GenMoveError("this vertical row is full of balls");
    }

    BLError Cube::MoveBack()
    {
        if (spendTurn == 0)
            return blet::GenMoveError("there is no ball");

        spendTurn--;

        for (Coordinate c = COOR4; c >= COOR1; c--)
        {
            if (GetSquare(Square{record[spendTurn].x, record[spendTurn].y, c}) != NOBALL)
            {
                SetSquare(Square{record[spendTurn].x, record[spendTurn].y, c}, NOBALL);
                record[spendTurn] = POSITIONERR;
                turn++;
                return blet::NoErr;
            }
        }

        return blet::NoErr;
    }

    Ball Cube::JudgeWinner()
    {
        int i;
        for (i = 0; i < MAX_LINES; i++)
        {
            if (GetSquare(DEFAULT_LINES[i][3]) == NOBALL)
                continue;
            if (
                GetSquare(DEFAULT_LINES[i][0]) == GetSquare(DEFAULT_LINES[i][1]) &&
                GetSquare(DEFAULT_LINES[i][1]) == GetSquare(DEFAULT_LINES[i][2]) &&
                GetSquare(DEFAULT_LINES[i][2]) == GetSquare(DEFAULT_LINES[i][3]))
            {
                return GetSquare(DEFAULT_LINES[i][0]);
            }
        }

        return NOBALL;
    }

    Ball Cube::GetTurn() { return turn; }

    int Cube::GetSpendTurn() { return spendTurn; }

    void Cube::GetRecord(Position rec[64])
    {
        for (int i = 0; i < 64; i++)
        {
            rec[i] = record[i];
        }
    }
}