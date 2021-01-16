//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Catapult.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Catapult::Catapult(IPlayer *ownedBy) : IBaseUnit(ownedBy) {
    _hp = 12;
    _attackPower = 6;
    _killReward = 10;
}

std::vector<int> Catapult::getAttackedPositions(int closestEnemy) {
    //TODO: use switch statement
    //TODO: deal with closestEnemy = 1
    if(closestEnemy == 2){
        return std::vector<int> {2,3};
    }
    else if( closestEnemy == 3 || closestEnemy == 4){
        return std::vector<int> {3,4};
    }
    else{
        return std::vector<int>();
    }
}

void Catapult::draw() {
    std::cout << "C";
}

IAction *Catapult::getAction(int actionNumber, std::vector<int> enemyDistances) {
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
            pResult = new ActionNone();
            break;
        }
        case 3:{

                pResult = new ActionMove(this,1);
            break;
        }
        default:
            std::cout << "Invalid Action Number" << std::endl;
    }
    delete p_lastAction;
    p_lastAction = pResult;
    return pResult;
}

Catapult::~Catapult() {
    delete p_lastAction;
    p_lastAction = nullptr;
}
