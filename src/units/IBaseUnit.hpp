//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IBASEUNIT_HPP
#define AGEOFWAR_IBASEUNIT_HPP


#include <vector>
#include "IAttackable.hpp"
#include "IAttacking.hpp"
#include "../utility/IDrawable.hpp"
#include "../players/IPlayer.hpp"
#include "../game/actions/IAction.hpp"

class IBaseUnit : public IAttackable,
                  public virtual IAttacking,
                  public virtual IDrawable {
public:
    explicit IBaseUnit(IPlayer *ownedBy) : p_owner(ownedBy) {}
    virtual ~IBaseUnit() = default;

    bool isOwnedBy(IPlayer *player) { return player == p_owner; }

    IPlayer *getOwner() const { return p_owner; }
    void setOwner(IPlayer* owner) { p_owner = owner; }

    virtual IAction *getAction(int actionNumber, std::vector<int> enemyDistances) = 0;
    virtual std::string print() = 0;

protected:
    IAction* p_lastAction = nullptr;
    IPlayer* p_owner = nullptr;
};

#endif //AGEOFWAR_IBASEUNIT_HPP