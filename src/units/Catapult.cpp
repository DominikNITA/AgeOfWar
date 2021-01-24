//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Catapult.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Catapult::Catapult(std::shared_ptr<IPlayer>ownedBy) : IBaseUnit(ownedBy) {
    _hp = 12;
    _attackPower = 6;
    _killReward = 10;
}

std::vector<int> Catapult::getAttackedPositions(int closestEnemy) {
    //TODO: use switch statement
    if (closestEnemy == 2) {
        return std::vector<int>{2, 3};
    } else if (closestEnemy == 3 || closestEnemy == 4) {
        return std::vector<int>{3, 4};
    } else {
        return std::vector<int>();
    }
}

void Catapult::draw() {
    std::cout << "C";
}

IAction *Catapult::getAction(int actionNumber, std::vector<int> enemyDistances) {
    IAction *pResult = nullptr;

    switch (actionNumber) {
        case 1: {
            auto attackedPositions = getAttackedPositions(enemyDistances.front());
            if (!attackedPositions.empty()) {
                pResult = new ActionAttack(std::shared_ptr<IAttacking>(this), attackedPositions);
                _hasFirstActionSucceeded = true;
            } else {
                pResult = new ActionNone();
                _hasFirstActionSucceeded = false;
            }
            break;
        }
        case 2: {
            pResult = new ActionNone();
            break;
        }
        case 3: {
            if(!_hasFirstActionSucceeded){
                pResult = new ActionMove(std::shared_ptr<IBaseUnit>(this), 1);
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

Catapult::~Catapult() {
    delete p_lastAction;
    p_lastAction = nullptr;
}
