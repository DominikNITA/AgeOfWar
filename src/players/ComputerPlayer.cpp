//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int i,GameLogger* gl) : IPlayer(i,gl) {
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
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(_colorCode) + "Player " + std::to_string(_number) + ConsoleHelper::getColorString(RESET) + " bought " + unitsInfo[index].first + " for " + ConsoleHelper::getColorString(YELLOW) + std::to_string(unitsInfo[index].second) + " coins");
    addCurrency(-unitsInfo[index].second);
    return index;
}
