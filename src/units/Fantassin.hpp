//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_FANTASSIN_HPP
#define AGEOFWAR_FANTASSIN_HPP


#include "IBaseUnit.hpp"
#include "IPurchasable.h"

class Fantassin : public IBaseUnit {
public:
    Fantassin(std::shared_ptr<IPlayer> ownedBy);
    ~Fantassin() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;
    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;

    std::string print() override {
        if(_isSuperSoldier) return "S";
        else return "F";
    }
    void upgradeToSuperSoldier() {_isSuperSoldier = true;}

private:
    bool _hasFirstActionSucceeded = false;
    bool _isSuperSoldier = false;
};


#endif //AGEOFWAR_FANTASSIN_HPP
