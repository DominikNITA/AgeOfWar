//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Archer.hpp"
#include "../game/actions/ActionNone.hpp"
#include "../game/actions/ActionAttack.hpp"
#include "../game/actions/ActionMove.hpp"

Archer::Archer(IPlayer *ownedBy)  : IBaseUnit(ownedBy){
    _price = 12;
    _hp = 8;
    _attackPower = 3;
    _killReward = 6;
}

void Archer::Draw() {
    std::cout << "A";
}

std::vector<int> Archer::GetAttackedPositions(int closestEnemy) {
    if( closestEnemy >= 1 && closestEnemy <= 3)
    {
        return std::vector<int> {closestEnemy};
    }
    else{
        return std::vector<int>();
    }
}

IAction* Archer::GetAction(int actionNumber, std::vector<int> enemyDistances) {
    IAction* pResult = nullptr;
    switch(actionNumber) {
        case 1:
            {
                if(enemyDistances.empty()) break;
                auto attackedPositions = GetAttackedPositions(enemyDistances.at(0));
                if (attackedPositions.empty())
                {
                    pResult = new ActionNone();
                }
                else
                    {
                        pResult = new ActionAttack(this,attackedPositions);
                }
            }
            break;
        case 2:
            pResult = new ActionMove(this,1);
            break;
        case 3:
            pResult = new ActionNone();
            break;
        default:
            std::cout << "Invalid Action Number" << std::endl;
    }
    return pResult;
}
