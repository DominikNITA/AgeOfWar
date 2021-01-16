//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "SuperSoldier.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

SuperSoldier::SuperSoldier(IPlayer *ownedBy) : IBaseUnit(ownedBy) {
    _hp = 10;
    _killReward = 5;
    _attackPower = 4;
}

std::vector<int> SuperSoldier::getAttackedPositions(int closestEnemy) {
    if(closestEnemy == 1){
        return std::vector<int> {1};
    }
    else {
        return std::vector<int>();
    }
}

void SuperSoldier::draw() {
    std::cout << "S";
}

IAction *SuperSoldier::getAction(int actionNumber, std::vector<int> enemyDistances) {
    IAction* pResult = nullptr;

    switch(actionNumber) {
        case 1:
        {
            auto attackedPositions = getAttackedPositions(enemyDistances.front());
            if(!attackedPositions.empty()){
                pResult = new ActionAttack(this, attackedPositions);
            }
            else{
                pResult = new ActionNone();
            }
            break;
        }
        case 2:
        {
            pResult = new ActionMove(this,1);
            break;
        }
        case 3:{
            //TODO: add logic for missing
            auto attackedPositions = getAttackedPositions(enemyDistances.front());
            if(attackedPositions.size() > 0){
                pResult = new ActionAttack(this, attackedPositions);
            }
            else{
                pResult = new ActionNone();
            }
            break;
        }
        default:
            std::cout << "Invalid Action Number" << std::endl;
    }
    delete p_lastAction;
    p_lastAction = pResult;
    return pResult;
}

SuperSoldier::~SuperSoldier() {
    delete p_lastAction;
    p_lastAction = nullptr;
}
