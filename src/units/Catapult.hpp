//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_CATAPULT_HPP
#define AGEOFWAR_CATAPULT_HPP


#include "IBaseUnit.hpp"

class Catapult : public IBaseUnit {
public:
    explicit Catapult(std::shared_ptr<IPlayer> ownedBy);
    Catapult();
    ~Catapult() override;

    std::vector<int> getAttackedPositions(int closestEnemy) override;

    IAction* getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) override;

    std::string print() override {
        return "C";
    }

private:
    bool m_hasFirstActionSucceeded = false;
    friend class cereal::access;

    template <class Archive>
    void serialize( Archive & archive )
    { archive( cereal::base_class<IBaseUnit>(this)); }
};
CEREAL_REGISTER_TYPE(Catapult)

#endif //AGEOFWAR_CATAPULT_HPP
