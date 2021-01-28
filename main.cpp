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

    // Header display
    std::cout << " Age of War - 2020/21 -"<<Helper::getColorString(BRIGHTBLUE)<<" Polytech Paris-Saclay "<<Helper::getColorString(RESET)<<"- Youssef MCHAREK, Dominik NITA" << std::endl
              << std::endl;

    // Case for new game
    if (argc>=3) {
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
        //Get unique game name used to save the game state to the 'saves' folder
        std::string name = argv[2];
        std::cout << " Game name : " << Helper::getColorString(BRIGHTBLUE) << name<< Helper::getColorString(RESET) << std::endl;
        std::cout << std::endl << Helper::getColorString(GREEN) << Helper::getColorString(BLINK) <<" Press enter to start the game..." << Helper::getColorString(RESET);
        //Await user input to continue
        getchar();
        //Erasing all previous information info except the header
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        Helper::erasePreviousLine();
        // Game preparation and execution
        GameManager game(mode,name);
        game.startGame();
    }
    // Case for loading an already existing game by name
    else if (argc == 2){
        GameManager game;
        // Get unique name used to load the game state
        std::string name = argv[1];
        std::cout << Helper::getColorString(GREEN) << "Loading save " << name << "..." << Helper::getColorString(RESET) << std::endl;
        // Create input stream
        std::ifstream is("saves/" + name + ".xml");
        // Create archive and start deserialization
        cereal::XMLInputArchive archive(is);
        archive(game);
        Helper::Sleep(2000);
        Helper::erasePreviousLine();
        // Start the game
        game.startGame();
    }
    // Case for not enough arguments passed
    else {
        std::cerr << "Not enough arguments. Aborting..." << std::endl;
        return 0;
    }

    // End of the program
    return 0;
}