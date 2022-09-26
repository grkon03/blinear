/*
evaluator.h

Definitions of the evaluator.
*/

#include "cube.h"

namespace blinear
{
    constexpr int MAX_BESTMOVES = 64;
    const std::string DEFAULT_WHITEPARAM_FILE = "../parameter/default/white";
    const std::string DEFAULT_BLACKPARAM_FILE = "../parameter/default/black";

    // evaluation parameters
    const double ONELINE_WORTH = 1;

    // evaluator class
    class Blinear
    {
    private:
        // the game board analyzed now
        Cube analyzed;

        // analyzed's evaluation
        double evaluation;

        // best moves
        Position bestMoves[MAX_BESTMOVES];

        // the lenght of best moves
        int bestMovesLength;

        // parameter of white(first player)
        double whiteParams[MAX_LINES];

        // parameter of black(second player)
        double blackParams[MAX_LINES];

    public:
        Blinear() : analyzed(Cube()), evaluation(0), bestMovesLength(0)
        {
            LoadParams(WHITE, DEFAULT_WHITEPARAM_FILE);
            LoadParams(BLACK, DEFAULT_WHITEPARAM_FILE);
        };
        BLError LoadParams(Ball, std::string);
        BLError SaveParams(Ball, std::string);
        BLError NewParamFile(std::string);
        BLError NewParamFile(std::string, double[MAX_LINES]);
    };
}