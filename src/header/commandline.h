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
        Blinear computer;

    public:
        CommandLine(BLCSetting setting) : setting(setting), computer(Blinear()){};
        CommandLine(BLCSetting setting, Blinear bl) : setting(setting), computer(bl){};

        BLError DisplayCube(Cube *);
        BLError PlayGameParser(Cube *, std::string, std::string *);
        void PlayGamePvP();
        void PlayGamePvC();
        void PlayGameCvC();
    };
}