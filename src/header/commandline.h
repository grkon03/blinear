#pragma once

#include "cube.h"
#include "util/error.h"

namespace blinear
{
    struct BLCSetting
    {
        bool displaySpendTurn;
    };

    class CommandLine
    {
    private:
        BLCSetting setting;

    public:
        CommandLine(BLCSetting setting) : setting(setting){};

        BLError DisplayCube(Cube *);
    };
}