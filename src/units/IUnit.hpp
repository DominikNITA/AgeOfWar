//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IUNIT_HPP
#define AGEOFWAR_IUNIT_HPP


#include <vector>
#include "IAttackable.hpp"
#include "IAttacking.h"
#include "../utility/IDrawable.hpp"
#include "../players/IPlayer.hpp"
#include "../game/actions/IAction.hpp"

class IUnit : public virtual IAttackable, public virtual IAttacking, public virtual IDrawable{
public:
    IUnit(IPlayer *ownedBy) : _ownedBy(ownedBy) { }
    bool IsOwnedBy(IPlayer *player) { return player == _ownedBy; }
    virtual IAction* GetAction(int actionNumber, std::vector<int> enemyDistances) = 0;
protected:
    IPlayer* _ownedBy;
};
#endif //AGEOFWAR_IUNIT_HPP