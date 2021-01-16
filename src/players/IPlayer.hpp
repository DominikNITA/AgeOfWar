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
    //Getters
    int GetCurrency() { return _currency; }
    Base* GetBase() { return &_base; }
    int GetNumber() {return  _number;}
    //Methods
    void addCurrency(int amount) { _currency += amount;}
    virtual int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) = 0;

protected:
    int _currency = 10;
    Base _base;
    int _number;
};
#endif //AGEOFWAR_IPLAYER_HPP