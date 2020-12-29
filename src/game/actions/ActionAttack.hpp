//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONATTACK_HPP
#define AGEOFWAR_ACTIONATTACK_HPP


#include "IAction.hpp"
#include "../../units/IAttacking.h"

class ActionAttack : public IAction{
public:
    ActionAttack(IAttacking* attacker) : _attacker(attacker) {}
    IAttacking* GetAttacker() {return _attacker;}
private:
    IAttacking*  _attacker;
};


#endif //AGEOFWAR_ACTIONATTACK_HPP
