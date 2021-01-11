//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP


#include "IBaseUnit.hpp"
#include "IPurchasable.h"

class Catapult : public IBaseUnit, public IPurchasable<Catapult> {
public:
    Catapult(IPlayer *ownedBy);

    std::vector<int> GetAttackedPositions(int closestEnemy) override;

    void Draw() override;
};


#endif //AGEOFWAR_CATAPULT_HPP
