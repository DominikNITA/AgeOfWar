//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IPLAYER_HPP
#define AGEOFWAR_IPLAYER_HPP


#include <vector>
#include "Base.hpp"

class IPlayer {
public:
    //Getters
    int GetCurrency() {return _currency;}
    Base GetBase() {return _base;}
    //Methods
    void AddCurrency(int amount) { _currency += amount; }

protected:
    int _currency;
    Base _base;
};
#endif //AGEOFWAR_IPLAYER_HPP