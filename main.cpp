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
    std::cout << " Age of War - 2020/21 -"<<Helper::getColorString(BRIGHTBLUE)<<" Polytech Paris-Saclay "<<Helper::getColorString(RESET)<<"- Youssef MCHAREK, Dominik NITA" << std::endl
              << std::endl;
    if (argc>=3) {
    // convert from *char to int to use switch
        int mode = std::stoi(argv[1]);
        switch ( mode )
        {
            case 1:
                std::cout << " Game mode :" << Helper::getColorString(BLUE) << " Player vs AI Easy" << std::endl;
                break;
            case 2:
                std::cout << " Game mode :" << Helper::getColorString(BLUE) << " Player vs Player" << std::endl;
                break;
            default:
                std::cerr << "Unknown game mode. Exiting!" << std::endl;
                return 0;
        }
        Helper::setColor(RESET);
        std::string name = argv[2];
        std::cout << " Game name : " << Helper::getColorString(BRIGHTBLUE) << name<< Helper::getColorString(RESET) << std::endl;
        std::cout << std::endl << Helper::getColorString(GREEN) << Helper::getColorString(BLINK) <<" Press any button to start..." << Helper::getColorString(RESET);
        getchar();
        //Erasing game information info except the header-title
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        // Game preparation and execution
        GameManager game(mode,name);
        game.startGame();
    } else if (argc == 2){
        GameManager game;
        std::string name = argv[1];
        std::cout << Helper::getColorString(GREEN) << "Loading save " << name << "..." << Helper::getColorString(RESET) << std::endl;
        std::ifstream is("saves/" + name + ".xml");
        cereal::XMLInputArchive archive(is);
        archive(game);
        Helper::Sleep(2000);
        Helper::erasePreviousLine();
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