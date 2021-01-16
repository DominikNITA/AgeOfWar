//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_COMPUTERPLAYER_HPP
#define AGEOFWAR_COMPUTERPLAYER_HPP


#include "IPlayer.hpp"

class ComputerPlayer : public IPlayer {

public:
    ComputerPlayer(int i);

    int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) override;
};


#endif //AGEOFWAR_COMPUTERPLAYER_HPP
