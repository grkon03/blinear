#include "error.h"

namespace blinear
{
    bool BLError::operator==(const BLError &b) { return (status == b.status); }
    bool BLError::operator!=(const BLError &b) { return (status != b.status); }
    std::string BLError::ErrorMessage()
    {
        std::string res;
        if (*this == blet::SetSquareErr)
            res = "Set Square Error";
        else if (*this == blet::MoveErr)
            res = "Move Error";
        else if (*this == blet::SetLineErr)
            res = "Set Line Error";
        else if (*this == blet::LoadParamErr)
            res = "Load Parameter Error";
        else if (*this == blet::SaveParamErr)
            res = "Save Parameter Error";
        else if (*this == blet::NewParamFileErr)
            res = "New Parameter File Error";
        else if (*this == blet::CommandParseErr)
            res = "Command Parse Error";
        else
            res = "Unexpected Error";

        res += " : " + message;

        return res;
    }

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

        BLError GenCommandParseError(std::string mes)
        {
            return BLError(700, mes);
        }
    }
}