//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_HUMANPLAYER_HPP
#define AGEOFWAR_HUMANPLAYER_HPP


#include "IPlayer.hpp"

class HumanPlayer : public IPlayer{

public:
    HumanPlayer(int i);

    int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) override;
};


#endif //AGEOFWAR_HUMANPLAYER_HPP
