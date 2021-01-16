//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Fantassin.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Fantassin::Fantassin(IPlayer *ownedBy) : IBaseUnit(ownedBy) {
    _hp = 10;
    _attackPower = 4;
    _killReward = 5;
}

std::vector<int> Fantassin::getAttackedPositions(int closestEnemy) {
    if(closestEnemy == 1){
        return std::vector<int> {1};
    }
    else {
        return std::vector<int>();
    }
}

void Fantassin::draw() {
    std::cout << "F";
}

IAction *Fantassin::getAction(int actionNumber, std::vector<int> enemyDistances) {
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
            if(!attackedPositions.empty()){
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

Fantassin::~Fantassin() {
    delete p_lastAction;
    p_lastAction = nullptr;
}
