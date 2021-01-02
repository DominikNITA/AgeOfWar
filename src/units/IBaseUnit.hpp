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

class IBaseUnit :   public virtual IAttackable,
                    public virtual IAttacking,
                    public virtual IDrawable{
public:
    IBaseUnit(IPlayer *ownedBy) : p_owner(ownedBy) { }
    bool IsOwnedBy(IPlayer *player) { return player == p_owner; }
    IPlayer* GetPlayer() {return p_owner;}
    virtual IAction* GetAction(int actionNumber, std::vector<int> enemyDistances) = 0;
protected:
    IPlayer* p_owner = nullptr;
};
#endif //AGEOFWAR_IBASEUNIT_HPP