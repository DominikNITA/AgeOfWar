//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include <utility>
#include "Fantassin.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Fantassin::Fantassin(std::shared_ptr<IPlayer> ownedBy) : IBaseUnit(std::move(ownedBy)) {
    m_hp = 10;
    m_attackPower = 4;
    m_killReward = 5;
}

Fantassin::Fantassin() : IBaseUnit(nullptr) {
    m_hp = 10;
    m_attackPower = 4;
    m_killReward = 5;
}

Fantassin::~Fantassin() {
    delete p_lastAction;
    p_lastAction = nullptr;
}

std::vector<int> Fantassin::getAttackedPositions(int closestEnemy) {
    if (closestEnemy == 1) {
        return std::vector<int>{1};
    } else {
        return std::vector<int>();
    }
}

IAction *Fantassin::getAction(int actionNumber, std::vector<int> enemyDistances,std::shared_ptr<IBaseUnit> selfReference) {
    IAction *pResult = nullptr;

    switch (actionNumber) {
        case 1: {
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
            pResult = new ActionMove(selfReference, 1);
            break;
        }
        case 3: {
            if (!m_hasFirstActionSucceeded || m_isSuperSoldier) {
                auto attackedPositions = getAttackedPositions(enemyDistances.front());
                if (!attackedPositions.empty()) {
                    pResult = new ActionAttack(selfReference, attackedPositions);
                } else {
                    pResult = new ActionNone();
                }
            } else {
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