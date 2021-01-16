//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP


#include "IBaseUnit.hpp"
#include "IPurchasable.h"

class Catapult : public IBaseUnit {
public:
    Catapult(IPlayer *ownedBy);

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;
};


#endif //AGEOFWAR_CATAPULT_HPP
