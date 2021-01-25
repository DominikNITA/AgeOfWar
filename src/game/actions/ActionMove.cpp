//
// Created by Dominik on 12/29/2020.
//

#include "ActionMove.hpp"

std::string ActionMove::GetActionLog() {
    return "Move action";
}

std::shared_ptr<IBaseUnit> ActionMove::getUnit() const {
    return m_unit;
}

int ActionMove::getCount() const {
    return m_count;
}
