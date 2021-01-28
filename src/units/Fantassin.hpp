//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_FANTASSIN_HPP
#define AGEOFWAR_FANTASSIN_HPP


#include "IBaseUnit.hpp"

class Fantassin : public IBaseUnit {
public:
    explicit Fantassin(std::shared_ptr<IPlayer> ownedBy);
    Fantassin();
    ~Fantassin() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    IAction *
    getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) override;

    std::string print() override {
        if(m_isSuperSoldier) return "S";
        else return "F";
    }
    void upgradeToSuperSoldier() { m_isSuperSoldier = true;}

private:
    bool m_hasFirstActionSucceeded = false;
    bool m_isSuperSoldier = false;

    friend class cereal::access;

    template <class Archive>
    void serialize( Archive & archive )
    { archive( cereal::base_class<IBaseUnit>(this),m_isSuperSoldier); }
};

CEREAL_REGISTER_TYPE(Fantassin)


#endif //AGEOFWAR_FANTASSIN_HPP
