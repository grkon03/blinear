#pragma once

#include <string>

namespace blinear
{
    class BLError
    {
    private:
        int status;
        std::string message;

    public:
        BLError() : status(0), message(""){};
        BLError(int status, std::string message) : status(status), message(message){};
        std::string ErrorMessage();

        bool operator==(const BLError &b);
        bool operator!=(const BLError &b);
    };

    namespace blet
    {
        BLError GenSetSquareError(std::string);
        BLError GenMoveError(std::string);
        BLError GenSetLineError(std::string);
        BLError GenLoadParamError(std::string);
        BLError GenSaveParamError(std::string);
        BLError GenNewParamFileError(std::string);
        BLError GenCommandParseError(std::string);

        const BLError NoErr = BLError();
        const BLError SetSquareErr = GenSetSquareError("");
        const BLError MoveErr = GenMoveError("");
        const BLError SetLineErr = GenSetLineError("");
        const BLError LoadParamErr = GenLoadParamError("");
        const BLError SaveParamErr = GenSaveParamError("");
        const BLError NewParamFileErr = GenNewParamFileError("");
        const BLError CommandParseErr = GenCommandParseError("");
    }
}