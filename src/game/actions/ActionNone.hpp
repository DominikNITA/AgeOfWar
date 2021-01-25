//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONNONE_HPP
#define AGEOFWAR_ACTIONNONE_HPP


#include "IAction.hpp"

class ActionNone : public IAction{
public:
    ActionNone();
    std::string GetActionLog() override;
};


#endif //AGEOFWAR_ACTIONNONE_HPP