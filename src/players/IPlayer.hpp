//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IPLAYER_HPP
#define AGEOFWAR_IPLAYER_HPP


#include <vector>
#include "../units/IUnit.hpp"

class IPlayer {
public:
    int GetCurrency() {return _currency;}
    const std::vector<IUnit> &getUnits() const { return _units; }
    int getBaseHp() const { return _baseHp ;}

protected:
    int _currency;
    std::vector<IUnit> _units;
    int _baseHp;
};
#endif //AGEOFWAR_IPLAYER_HPP