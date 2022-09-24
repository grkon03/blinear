#include "error.h"

namespace blinear
{
    namespace blet
    {
        BLError GenSetSquareError(std::string mes)
        {
            return BLError(100, mes);
        }

        BLError GenMoveError(std::string mes)
        {
            return BLError(200, mes);
        }
    }
}