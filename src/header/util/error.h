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
        BLError() : status(0), message(0){};
        BLError(int status, std::string message) : status(status), message(message){};

        bool operator==(const BLError &b);
        bool operator!=(const BLError &b);
    };

    namespace blet
    {
        BLError GenSetSquareError(std::string);
        BLError GenMoveError(std::string);
        BLError GenSetLineError(std::string);

        const BLError NoErr = BLError();
        const BLError SetSquareErr = GenSetSquareError("");
        const BLError MoveErr = GenMoveError("");
        const BLError SetLineErr = GenSetLineError("");
    }
}