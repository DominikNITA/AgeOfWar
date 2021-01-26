//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IBASEUNIT_HPP
#define AGEOFWAR_IBASEUNIT_HPP


#include <vector>
#include <memory>
#include "IAttackable.hpp"
#include "IAttacking.hpp"
#include "../players/IPlayer.hpp"
#include "../game/actions/IAction.hpp"


class IBaseUnit : public IAttackable,
                  public virtual IAttacking{
public:
    explicit IBaseUnit(std::shared_ptr<IPlayer>ownedBy) : p_owner(ownedBy) {}
    virtual ~IBaseUnit() = default;

    std::shared_ptr<IPlayer> getOwner() const { return p_owner; }
    void setOwner(std::shared_ptr<IPlayer> owner) { p_owner = owner; }

    bool isOwnedBy(std::shared_ptr<IPlayer>player) { return player == p_owner; }


    virtual IAction *getAction(int actionNumber, std::vector<int> enemyDistances, std::shared_ptr<IBaseUnit> selfReference) = 0;
    virtual std::string print() = 0;

protected:
    IAction* p_lastAction = nullptr;
    std::shared_ptr<IPlayer> p_owner = nullptr;
};

#endif //AGEOFWAR_IBASEUNIT_HPP