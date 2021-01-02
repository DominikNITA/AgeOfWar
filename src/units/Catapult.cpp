//
// Created by dominik on 12/27/20.
//

#include <iostream>
#include "Catapult.hpp"

Catapult::Catapult(IPlayer *ownedBy) : IBaseUnit(ownedBy) {
    _price = 20;
    _hp = 12;
    _attackPower = 6;
    _killReward = 10;
}

std::vector<int> Catapult::GetAttackedPositions(int closestEnemy) {
    //TODO: use switch statement
    //TODO: deal with closestEnemy = 1
    if(closestEnemy == 2){
        return std::vector<int> {2,3};
    }
    else if( closestEnemy == 3 || closestEnemy == 4){
        return std::vector<int> {3,4};
    }
    else{
        return std::vector<int>();
    }
}

void Catapult::Draw() {
    std::cout << "C";
}
