//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_FANTASSIN_HPP
#define AGEOFWAR_FANTASSIN_HPP


#include "IBaseUnit.hpp"
#include "IPurchasable.h"

class Fantassin : public IBaseUnit {
public:
    Fantassin(IPlayer *ownedBy);
    std::vector<int> getAttackedPositions(int closestEnemy) override;
    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;

    ~Fantassin() override;
};


#endif //AGEOFWAR_FANTASSIN_HPP
