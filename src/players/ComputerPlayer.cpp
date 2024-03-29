#include <iostream>
#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(int i,std::shared_ptr<GameLogger> gl) : IPlayer(i,"AI Easy",gl) {}
ComputerPlayer::ComputerPlayer(int number, std::string name, int colorCode, int currency, std::shared_ptr<Base> base) : IPlayer(number,name,nullptr) {
    m_colorCode = colorCode;
    m_currency = currency;
    p_base = base;
}

int ComputerPlayer::chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) {
    int maxPrice = 0;
    int index = 0;
    for (int i = 0; i < unitsInfo.size(); ++i) {
        if(unitsInfo[i].second <= m_currency && unitsInfo[i].second >= maxPrice){
            maxPrice = unitsInfo[i].second;
            index=i;
        }
    }
    p_gameLogger->logAndDraw(Helper::getColorString(m_colorCode) + "Player " + std::to_string(m_number) + Helper::getColorString(RESET) + " bought " + unitsInfo[index].first + " for " + Helper::getColorString(YELLOW) + std::to_string(unitsInfo[index].second) + " coins");
    addCurrency(-unitsInfo[index].second);
    return index;
}
