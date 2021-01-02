//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_SUPERSOLDIER_HPP
#define AGEOFWAR_SUPERSOLDIER_HPP


#include "IBaseUnit.hpp"

class SuperSoldier : public IBaseUnit{
    SuperSoldier(IPlayer *ownedBy);

public:
    std::vector<int> GetAttackedPositions(int closestEnemy) override;

    void Draw() override;
};


#endif //AGEOFWAR_SUPERSOLDIER_HPP
