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
    };

    namespace blet
    {
        BLError GenSetSquareError(std::string);

        const BLError NoErr = BLError();
        const BLError SetSquareErr = GenSetSquareError("");
    }
}