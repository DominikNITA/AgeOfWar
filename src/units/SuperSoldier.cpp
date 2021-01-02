//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "SuperSoldier.hpp"

SuperSoldier::SuperSoldier(IPlayer *ownedBy) : IBaseUnit(ownedBy) {
    _hp = 10;
    _killReward = 5;
    _attackPower = 4;
}

std::vector<int> SuperSoldier::GetAttackedPositions(int closestEnemy) {
    if(closestEnemy == 1){
        return std::vector<int> {1};
    }
    else {
        return std::vector<int>();
    }
}

void SuperSoldier::Draw() {
    std::cout << "S";
}
