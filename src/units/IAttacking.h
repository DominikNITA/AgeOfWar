//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_IATTACKING_H
#define AGEOFWAR_IATTACKING_H


#include <vector>

class IAttacking {
public:
    int GetAttackPower() { return _attackPower; }
    virtual std::vector<int> GetAttackedPositions(int closestEnemy) = 0;
protected:
    int _attackPower;
};


#endif //AGEOFWAR_IATTACKING_H
