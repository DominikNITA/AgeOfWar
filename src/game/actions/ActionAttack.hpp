//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONATTACK_HPP
#define AGEOFWAR_ACTIONATTACK_HPP


#include "IAction.hpp"
#include "../../units/IAttacking.hpp"
#include <memory>

class ActionAttack : public IAction{
public:
    ActionAttack(std::shared_ptr<IAttacking> attacker, std::vector<int> attackedPositions) : _attacker(attacker), _attackedPositions(attackedPositions) {}
    std::shared_ptr<IAttacking> GetAttacker() {return _attacker;}
    std::vector<int> GetAttackedPositions() {return _attackedPositions;}

    std::string GetActionLog() override;

private:
    std::shared_ptr<IAttacking>  _attacker;
    std::vector<int> _attackedPositions;
};


#endif //AGEOFWAR_ACTIONATTACK_HPP
