//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP


#include "IBaseUnit.hpp"

class Catapult : public IBaseUnit {
public:
    Catapult(std::shared_ptr<IPlayer> ownedBy);
    ~Catapult() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) override;

    std::string print() override {
        return "C";
    }

private:
    bool m_hasFirstActionSucceeded = false;
};


#endif //AGEOFWAR_CATAPULT_HPP
