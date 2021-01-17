//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int i) : IPlayer(i) {
    _colorCode = 36;
}

int ComputerPlayer::chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) {
    int maxPrice = 0;
    int index = 0;
    for (int i = 0; i < unitsInfo.size(); ++i) {
        if( unitsInfo[i].second <= _currency && unitsInfo[i].second >= maxPrice){
            maxPrice = unitsInfo[i].second;
            index=i;
        }
    }
//    std::cout << "AI money before deduction: " << _currency << std::endl;
    addCurrency(-unitsInfo[index].second);
    return index;
}
