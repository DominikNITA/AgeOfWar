//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IPLAYER_HPP
#define AGEOFWAR_IPLAYER_HPP


#include <vector>
#include "Base.hpp"

class IPlayer {
public:
    IPlayer(int number);

    virtual ~IPlayer() {
        delete p_base;
    }

    //Getters
    int GetCurrency() { return _currency; }
    Base* GetBase() { return p_base; }
    int GetNumber() {return  _number;}
    int getColorCode() {return _colorCode; }
    //Methods
    void addCurrency(int amount) { _currency += amount;}
    virtual int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) = 0;

protected:
    int _currency = 10;
    Base* p_base;
    int _number;
    int _colorCode;
};
#endif //AGEOFWAR_IPLAYER_HPP