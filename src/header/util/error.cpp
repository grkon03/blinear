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

        BLError GenSetLineError(std::string mes)
        {
            return BLError(300, mes);
        }

        BLError GenLoadParamError(std::string mes)
        {
            return BLError(400, mes);
        }

        BLError GenSaveParamError(std::string mes)
        {
            return BLError(500, mes);
        }

        BLError GenNewParamFileError(std::string mes)
        {
            return BLError(600, mes);
        }
    }
}