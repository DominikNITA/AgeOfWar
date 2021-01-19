#include <iostream>
#include <chrono>
#include "src/units/Archer.hpp"
#include "src/units/Fantassin.hpp"
#include "src/players/HumanPlayer.hpp"
#include "src/game/GameManager.hpp"
#include "src/units/SuperSoldier.hpp"

using namespace std;


int main() {
    // Start of the program
    //auto t_start = std::chrono::system_clock::now();
    //std::time_t time_start = std::chrono::system_clock::to_time_t(t_start);
    //std::cout << "Program started at: "  << std::ctime(&time_start) << std::endl;

    // Memory on start

    // Game preparation and execution
    auto game = new GameManager(1);
    game->startGame();
    delete game;
    // Memory on stop

    // End of the program
    //auto t_stop = std::chrono::system_clock::now();
    //std::time_t time_stop = std::chrono::system_clock::to_time_t(t_stop);
    //std::cout << "Program stopped at: " << std::ctime(&time_stop) << std::endl;
    return 0;
}