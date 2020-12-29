//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Fantassin.hpp"

Fantassin::Fantassin(IPlayer *ownedBy) : IUnit(ownedBy) {
    _price = 10;
    _hp = 10;
    _attackPower = 4;
    _killReward = 5;
}

std::vector<int> Fantassin::GetAttackedPositions(int closestEnemy) {
    if(closestEnemy == 1){
        return std::vector<int> {1};
    }
    else {
        return std::vector<int>();
    }
}

void Fantassin::Draw() {
    std::cout << "F";
}
