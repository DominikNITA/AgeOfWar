//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_SUPERSOLDIER_HPP
#define AGEOFWAR_SUPERSOLDIER_HPP


#include "IBaseUnit.hpp"

class SuperSoldier : public IBaseUnit{
    SuperSoldier(IPlayer *ownedBy);

public:
    std::vector<int> getAttackedPositions(int closestEnemy) override;

    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;

    ~SuperSoldier() override;
};


#endif //AGEOFWAR_SUPERSOLDIER_HPP
