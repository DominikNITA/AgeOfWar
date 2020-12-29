#include <iostream>
#include "src/units/Archer.hpp"
#include "src/units/Fantassin.hpp"
#include "src/players/HumanPlayer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    IPlayer *player = new HumanPlayer();
    Archer archer(player);
    std::cout << archer.GetHp()<< std::endl;
    archer.Draw();
//    fant.Draw();
//    std::cout << fant.GetAttackedPositions(1).at(0) << std::endl;
    return 0;
}