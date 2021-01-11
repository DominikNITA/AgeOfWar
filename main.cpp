#include <iostream>
#include <chrono>
#include "src/units/Archer.hpp"
#include "src/units/Fantassin.hpp"
#include "src/players/HumanPlayer.hpp"
#include "src/game/GameManager.hpp"

using namespace std;


int main() {

    // Start of the program
    auto t_start = std::chrono::system_clock::now();
    std::time_t time_start = std::chrono::system_clock::to_time_t(t_start);
    std::cout << "Program started at: "  << std::ctime(&time_start) << std::endl;

    // Memory on start

    // Game preparation and exectution
    GameManager game(1);
    game.StartGame();
//    fant.Draw();
//    std::cout << fant.GetAttackedPositions(1).at(0) << std::endl;

    // Memory on stop

    // End of the program
    auto t_stop = std::chrono::system_clock::now();
    std::time_t time_stop = std::chrono::system_clock::to_time_t(t_stop);
    std::cout << "Program stopped at: " << std::ctime(&time_stop) << std::endl;
    return 0;
}