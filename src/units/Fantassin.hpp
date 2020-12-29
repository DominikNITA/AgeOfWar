//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_FANTASSIN_HPP
#define AGEOFWAR_FANTASSIN_HPP


#include "IUnit.hpp"
#include "IPurchasable.h"

class Fantassin : public IUnit, public IPurchasable {
public:
    Fantassin(IPlayer *ownedBy);
    std::vector<int> GetAttackedPositions(int closestEnemy) override;
    void Draw() override;
};


#endif //AGEOFWAR_FANTASSIN_HPP
