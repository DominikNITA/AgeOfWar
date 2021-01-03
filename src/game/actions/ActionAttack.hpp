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

    std::string GetActionLog() override;

private:
    IAttacking*  _attacker;
    std::vector<int> _attackedPositions;
};


#endif //AGEOFWAR_ACTIONATTACK_HPP
