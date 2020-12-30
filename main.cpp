#include <iostream>
#include "src/units/Archer.hpp"
#include "src/units/Fantassin.hpp"
#include "src/players/HumanPlayer.hpp"
#include "src/game/Game.hpp"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Game game(1);
    game.StartGame();
//    fant.Draw();
//    std::cout << fant.GetAttackedPositions(1).at(0) << std::endl;
    return 0;
}