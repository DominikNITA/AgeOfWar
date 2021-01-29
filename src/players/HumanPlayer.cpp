#include <algorithm>
#include <iostream>
#include "HumanPlayer.hpp"
#include "../utility/Helper.hpp"
#include <thread>
#include <utility>

using std::cout;using std::endl; using std::cin;

HumanPlayer::HumanPlayer(int i,std::string n,std::shared_ptr<GameLogger> p) : IPlayer(i,std::move(n),std::move(p)) {}

HumanPlayer::HumanPlayer(int number, std::string name, int colorCode, int currency, std::shared_ptr<Base> base) : IPlayer(number,std::move(name),nullptr) {
    m_colorCode = colorCode;
    m_currency = currency;
    p_base = std::move(base);
}

int HumanPlayer::chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) {

    int choice = -1;
    while (choice < 0) {
        cout << endl << Helper::getColorString(CYAN) << "Unit Shop:" << endl;
        cout << "Coins: " << Helper::getColorString(YELLOW) << m_currency << endl;
        for (int i = 0; i < unitsInfo.size(); ++i) {
            if(unitsInfo[i].second <= m_currency){
                Helper::setColor(GREEN);
            }
            else{
                Helper::setColor(RED);
            }
            cout << " " << i << ". Buy " << unitsInfo[i].first << " for " << unitsInfo[i].second << " coins" << endl;
            Helper::setColor(RESET);
        }

        Helper::setColor(BRIGHTWHITE);
        cout << "Choose number of the unit you want to buy: ";
        //TODO: parse int and check for invalid input
        cin >> choice;
        for (int i = 0; i < unitsInfo.size()+4; ++i) {
            Helper::moveCursorUp();
            Helper::eraseLine();
        }
        if (choice < 0 || choice > unitsInfo.size() - 1) {
            choice = -1; // reset choice for loop condition
            Helper::setColor(RED);
            Helper::setColor(BLINK);
            cout << "Invalid unit number. Try again!" << endl;
            Helper::setColor(RESET);
            //Sleep from https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
            Helper::Sleep(2500);
            Helper::moveCursorUp();
            Helper::eraseLine();
        }
        else if(unitsInfo[choice].second > m_currency){
            Helper::setColor(RED);
            Helper::setColor(BLINK);
            cout << "Not enough coins. Try with other unit!" << endl;
            Helper::setColor(RESET);
            Helper::Sleep(2500);
            Helper::moveCursorUp();
            Helper::eraseLine();
            choice = -1;
        }
    }

    p_gameLogger->logAndDraw(Helper::getColorString(m_colorCode) + "Player " + std::to_string(m_number) + Helper::getColorString(RESET) + " bought " + unitsInfo[choice].first + " for " + Helper::getColorString(YELLOW) + std::to_string(unitsInfo[choice].second) + " coins");

    addCurrency(-unitsInfo[choice].second);

    return choice;
}


