#include <iostream>
#include <fstream>
#include <chrono>
#include "src/game/GameManager.hpp"
#include <cereal/cereal.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>

using namespace std;


int main(int argc, char * argv[]) {
    // Start of the program
    //auto t_start = std::chrono::system_clock::now();
    //std::time_t time_start = std::chrono::system_clock::to_time_t(t_start);
    //std::cout << "Program started at: "  << std::ctime(&time_start) << std::endl;

    // Memory on start

    if (argc>=3) {
    // convert from *char to int to use switch
        int mode = std::stoi(argv[1]);
        switch ( mode )
        {
            case 1:
            case 2:
                std::cout << "Game mode : " << mode << std::endl;
                break;
            default:
                std::cerr << "Unknown game mode." << std::endl;
                return 0;
        }
        std::string name = argv[2];
        std::cout << "Game name : " << name <<". Starting in few seconds" << std::endl;
        Helper::Sleep(2000);
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        // Game preparation and execution
        GameManager game(mode,name);
        game.startGame();
    } else if (argc == 2){
        GameManager game;
        std::string name = argv[1];
        std::ifstream is("saves/" + name + ".xml");
        cereal::XMLInputArchive archive(is);
        archive(game);
        Helper::Sleep(10000);
        game.startGame();
    } else {
        std::cerr << "Not enough arguments. Aborting..." << std::endl;
        return 0;
    }
    // Memory on stop

    // End of the program
    //auto t_stop = std::chrono::system_clock::now();
    //std::time_t time_stop = std::chrono::system_clock::to_time_t(t_stop);
    //std::cout << "Program stopped at: " << std::ctime(&time_stop) << std::endl;
    return 0;
}