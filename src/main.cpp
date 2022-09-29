#include "collection.h"
#include <iostream>

using namespace blinear;

int main()
{
    Blinear bl;
    Cube game;
    BLError err;
    CommandLine cm(BLCSetting{true});
    std::string str;
    Coordinate x, y;
    int _x, _y;

    while (game.JudgeWinner() == NOBALL || game.GetSpendTurn() == 64)
    {
        cm.DisplayCube(&game);
        std::cout << "評価値 : " << bl.evaluate(game) << std::endl;
        std::cout << "次のムーブ > ";
        std::getline(std::cin, str);
        _x = stoi(str.substr(0, 1));
        _y = stoi(str.substr(1, 1));
        if (_x < 1 || 4 < _x || _y < 1 || 4 < _y)
        {
            std::cout << "失敗しました" << std::endl
                      << std::endl;
            continue;
        }
        x = Coordinate(_x - 1);
        y = Coordinate(_y - 1);
        err = game.Move(Position{x, y});
        if (err != blet::NoErr)
        {
            std::cout << "失敗しました" << std::endl
                      << std::endl;
            continue;
        }
    }
    switch (game.JudgeWinner())
    {
    case WHITE:
        std::cout << "白の勝ち" << std::endl;
        break;
    case BLACK:
        std::cout << "黒の勝ち" << std::endl;
        break;
    case NOBALL:
        std::cout << "ひきわけ" << std::endl;
    }
}