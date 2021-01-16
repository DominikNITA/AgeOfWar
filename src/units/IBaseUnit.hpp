//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IBASEUNIT_HPP
#define AGEOFWAR_IBASEUNIT_HPP


#include <vector>
#include "IAttackable.hpp"
#include "IAttacking.h"
#include "../utility/IDrawable.hpp"
#include "../players/IPlayer.hpp"
#include "../game/actions/IAction.hpp"

class IBaseUnit : public virtual IAttackable,
                  public virtual IAttacking,
                  public virtual IDrawable {
public:
    explicit IBaseUnit(IPlayer *ownedBy) : p_owner(ownedBy) {}

    bool isOwnedBy(IPlayer *player) { return player == p_owner; }

    IPlayer *getOwner() { return p_owner; }
    void setOwner(IPlayer* owner) { p_owner = owner; }

    virtual IAction *getAction(int actionNumber, std::vector<int> enemyDistances) = 0;

protected:
    IPlayer *p_owner = nullptr;
};

#endif //AGEOFWAR_IBASEUNIT_HPP