//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Catapult.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Catapult::Catapult(std::shared_ptr<IPlayer>ownedBy) : IBaseUnit(ownedBy) {
    m_hp = 12;
    m_attackPower = 6;
    m_killReward = 10;
}

std::vector<int> Catapult::getAttackedPositions(int closestEnemy) {
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

IAction *Catapult::getAction(int actionNumber, std::vector<int> enemyDistances,
                             std::shared_ptr<IBaseUnit> selfReference) {
    IAction *pResult = nullptr;

    switch (actionNumber) {
        case 1: {
            //TODO: merde
            auto attackedPositions = getAttackedPositions(enemyDistances.front());
            if (!attackedPositions.empty()) {
                pResult = new ActionAttack(selfReference, attackedPositions);
                m_hasFirstActionSucceeded = true;
            } else {
                pResult = new ActionNone();
                m_hasFirstActionSucceeded = false;
            }
            break;
        }
        case 2: {
            pResult = new ActionNone();
            break;
        }
        case 3: {
            if(!m_hasFirstActionSucceeded){
                pResult = new ActionMove(selfReference, 1);
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
