//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "HumanPlayer.hpp"
#include "../utility/ConsoleHelper.hpp"
#include <chrono>
#include <thread>

using std::cout;using std::endl; using std::cin;

HumanPlayer::HumanPlayer(int i) : IPlayer(i) {
    _colorCode = 35;
}

int HumanPlayer::chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) {
    cout << "Unit Shop:" << endl;
    cout << "Coins: " << ConsoleHelper::getColorString(YELLOW) << _currency << endl;
    int choice = -1;
    while (choice < 0) {

        for (int i = 0; i < unitsInfo.size(); ++i) {
            if(unitsInfo[i].second <= _currency){
                ConsoleHelper::setColor(GREEN);
            }
            else{
                ConsoleHelper::setColor(RED);
            }
            cout << i << ". Buy " << unitsInfo[i].first << " for " << unitsInfo[i].second << " coins" << endl;
            ConsoleHelper::setColor(RESET);
        }
        ConsoleHelper::setColor(RESET);
        cout << "Choose unit to buy:";
        //TODO: parse int
        cin >> choice;
        for (int i = 0; i < unitsInfo.size()+3; ++i) {
            ConsoleHelper::moveCursorUp();
            ConsoleHelper::eraseLine();
        }
        if (choice < 0 || choice > unitsInfo.size() - 1) {
            choice = -1; // reset choice for loop condition
            ConsoleHelper::setColor(RED);
            ConsoleHelper::setColor(UNDERLINE);
            cout << "Invalid unit number. Try again!" << endl;
            ConsoleHelper::setColor(RESET);
            //Sleep from https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ConsoleHelper::moveCursorUp();
            ConsoleHelper::eraseLine();
        }
        else if(unitsInfo[choice].second > _currency){
            ConsoleHelper::setColor(RED);
            ConsoleHelper::setColor(UNDERLINE);
            cout << "Not enough coins. Try with other unit!" << endl;
            ConsoleHelper::setColor(RESET);
            //Sleep from https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ConsoleHelper::moveCursorUp();
            ConsoleHelper::eraseLine();
            choice = -1;
        }
    }
    addCurrency(-unitsInfo[choice].second);
    return choice;
}
