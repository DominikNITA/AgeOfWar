//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONMOVE_HPP
#define AGEOFWAR_ACTIONMOVE_HPP


#include "IAction.hpp"
#include "../../units/IBaseUnit.hpp"

class ActionMove : public IAction{
public:
    ActionMove(IBaseUnit* unit, int count) : _unit(unit), _count(count) {}
    std::string GetActionLog() override;
    IBaseUnit *getUnit() const;
    int getCount() const;

private:
    IBaseUnit* _unit;
    int _count;
};


#endif //AGEOFWAR_ACTIONMOVE_HPP
