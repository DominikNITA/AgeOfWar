//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int i) : IPlayer(i) {

}

int ComputerPlayer::chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) {
    std::cout << "Computer choosed his unit!" << std::endl;
    return 0;
}
