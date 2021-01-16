//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_ARCHER_HPP
#define AGEOFWAR_ARCHER_HPP


#include "IBaseUnit.hpp"
#include "IPurchasable.h"

class Archer : public IBaseUnit{
public:
    Archer(IPlayer *ownedBy);
    std::vector<int> getAttackedPositions(int closestEnemy) override;
    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;
};


#endif //AGEOFWAR_ARCHER_HPP
