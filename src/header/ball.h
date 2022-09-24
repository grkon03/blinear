/*
ball.h

Definitions of the balls of 3 dimensional 4 in a row.
*/

#pragma once

namespace blinear
{
    enum Ball : int
    {
        NOBALL = 0,
        WHITE,
        BLACK,
    };

    inline Ball operator++(Ball b, int)
    {
        return (b == NOBALL) ? NOBALL : Ball(3 - (int)b);
    }
}