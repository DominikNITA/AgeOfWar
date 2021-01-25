//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_IATTACKING_HPP
#define AGEOFWAR_IATTACKING_HPP


#include <vector>

class IAttacking {
public:
    int GetAttackPower() const { return m_attackPower; }
    virtual std::vector<int> getAttackedPositions(int closestEnemy) = 0;
protected:
    int m_attackPower;
};


#endif //AGEOFWAR_IATTACKING_HPP
