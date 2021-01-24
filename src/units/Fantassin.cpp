//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Fantassin.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionMove.hpp"

Fantassin::Fantassin(std::shared_ptr<IPlayer> ownedBy) : IBaseUnit(ownedBy) {
    _hp = 10;
    _attackPower = 4;
    _killReward = 5;
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

void Fantassin::draw() {
    if(_isSuperSoldier) std::cout << "S";
    else std::cout << "F";
}

IAction *Fantassin::getAction(int actionNumber, std::vector<int> enemyDistances) {
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
            pResult = new ActionMove(std::shared_ptr<IBaseUnit>(this), 1);
            break;
        }
        case 3: {
            if (!_hasFirstActionSucceeded || _isSuperSoldier) {
                auto attackedPositions = getAttackedPositions(enemyDistances.front());
                if (!attackedPositions.empty()) {
                    pResult = new ActionAttack(std::shared_ptr<IAttacking>(this), attackedPositions);
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