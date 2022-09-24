#include "error.h"

namespace blinear
{
    bool BLError::operator==(const BLError &b) { return (status == b.status); }
    bool BLError::operator!=(const BLError &b) { return (status != b.status); }

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