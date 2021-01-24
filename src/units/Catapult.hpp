//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP


#include "IBaseUnit.hpp"

class Catapult : public IBaseUnit {
public:
    Catapult(std::shared_ptr<IPlayer> ownedBy);

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    void draw() override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances) override;

    std::string print() override {
        return "C";
    }

    ~Catapult() override;
private:
    bool _hasFirstActionSucceeded = false;
};


#endif //AGEOFWAR_CATAPULT_HPP
