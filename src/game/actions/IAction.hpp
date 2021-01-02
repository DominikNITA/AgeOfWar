//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_IACTION_HPP
#define AGEOFWAR_IACTION_HPP


#include <string>

class IAction {
public:
    virtual std::string GetActionLog() = 0;
};


#endif //AGEOFWAR_IACTION_HPP
