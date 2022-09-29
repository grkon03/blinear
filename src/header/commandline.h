#pragma once

#include "cube.h"
#include "blinear.h"
#include "util/error.h"

namespace blinear
{
    struct BLCSetting
    {
        bool displaySpendTurn;
        bool displayEvaluation;
        bool displayBestMoves;
    };

    class CommandLine
    {
    private:
        BLCSetting setting;

    public:
        CommandLine(BLCSetting setting) : setting(setting){};

        BLError DisplayCube(Cube *);
        BLError PlayGameParser(Blinear, Cube *, std::string, std::string *);
        void PlayGamePvP();
        void PlayGamePvC();
        void PlayGameCvC();
    };
}