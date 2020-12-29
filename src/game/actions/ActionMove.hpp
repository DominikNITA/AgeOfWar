//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONMOVE_HPP
#define AGEOFWAR_ACTIONMOVE_HPP


#include "IAction.hpp"
#include "../../units/IUnit.hpp"

class ActionMove : public IAction{
public:
    ActionMove(IUnit* unit, int count) : _unit(unit), _count(count) {}
private:
    IUnit* _unit;
    int _count;
};


#endif //AGEOFWAR_ACTIONMOVE_HPP
