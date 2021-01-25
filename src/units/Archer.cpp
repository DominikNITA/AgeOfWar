//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Archer.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionMove.hpp"

Archer::Archer(std::shared_ptr<IPlayer> ownedBy) : IBaseUnit(ownedBy) {
    m_hp = 8;
    m_attackPower = 3;
    m_killReward = 6;
}

void Archer::draw() {
    std::cout << "A";
}

std::vector<int> Archer::getAttackedPositions(int closestEnemy) {
    if (closestEnemy >= 1 && closestEnemy <= 3) {
        return std::vector<int>{closestEnemy};
    } else {
        return std::vector<int>();
    }
}

IAction *Archer::getAction(int actionNumber, std::vector<int> enemyDistances,
                           std::shared_ptr<IBaseUnit> selfReference) {
    IAction *pResult = nullptr;
    switch (actionNumber) {
        case 1: {
            if (enemyDistances.empty()) break;
            auto attackedPositions = getAttackedPositions(enemyDistances.at(0));
            if (attackedPositions.empty()) {
                pResult = new ActionNone();
            } else {
                pResult = new ActionAttack(selfReference, attackedPositions);
            }
        }
            break;
        case 2:
            pResult = new ActionMove(selfReference, 1);
            break;
        case 3:
            pResult = new ActionNone();
            break;
        default:
            std::cout << "Invalid Action Number" << std::endl;
    }

    delete p_lastAction;
    p_lastAction = pResult;
    return pResult;
}

Archer::~Archer() {
    delete p_lastAction;
    p_lastAction = nullptr;
}
