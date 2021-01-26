//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_ARCHER_HPP
#define AGEOFWAR_ARCHER_HPP


#include "IBaseUnit.hpp"

class Archer : public IBaseUnit{
public:
    Archer(std::shared_ptr<IPlayer> ownedBy);
    ~Archer() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    IAction *
    getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) override;

    std::string print() override {
        return std::string("A");
    }
};


#endif //AGEOFWAR_ARCHER_HPP