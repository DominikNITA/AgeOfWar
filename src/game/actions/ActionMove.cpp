//
// Created by Dominik on 12/29/2020.
//

#include "ActionMove.hpp"

std::string ActionMove::GetActionLog() {
    return "Move action";
}

IBaseUnit *ActionMove::getUnit() const {
    return _unit;
}

int ActionMove::getCount() const {
    return _count;
}
