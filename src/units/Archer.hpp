//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_ARCHER_HPP
#define AGEOFWAR_ARCHER_HPP


#include "IBaseUnit.hpp"

class Archer : public IBaseUnit{
public:
    explicit Archer(std::shared_ptr<IPlayer> ownedBy);
    Archer();
    ~Archer() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    IAction *
    getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) override;

    std::string print() override {
        return std::string("A");
    }
    friend class cereal::access;

    template <class Archive>
    void serialize( Archive & archive )
    { archive( cereal::base_class<IBaseUnit>(this)); }
};
CEREAL_REGISTER_TYPE(Archer)

#endif //AGEOFWAR_ARCHER_HPP