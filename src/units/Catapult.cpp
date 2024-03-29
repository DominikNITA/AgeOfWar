#include <iostream>
#include <utility>
#include "Catapult.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Catapult::Catapult(std::shared_ptr<IPlayer> ownedBy) : IBaseUnit(std::move(ownedBy)) {
    m_hp = 12;
    m_attackPower = 6;
    m_killReward = 10;
}

Catapult::Catapult() : IBaseUnit(nullptr) {
    m_hp = 12;
    m_attackPower = 6;
    m_killReward = 10;
}

Catapult::~Catapult() {
    delete p_lastAction;
    p_lastAction = nullptr;
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

IAction* Catapult::getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) {
    IAction *pResult = nullptr;

    switch (actionNumber) {
        case 1: {
            int closestEnemy = enemyDistances.front();
            //when closest enemy is just in front, then the catapult should aim at the second closest
            if (closestEnemy == 1 && enemyDistances.size() >= 2) {
                closestEnemy = enemyDistances[1];
            }
            auto attackedPositions = getAttackedPositions(closestEnemy);
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
            if (!m_hasFirstActionSucceeded) {
                pResult = new ActionMove(selfReference, 1);
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
