//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_IACTION_HPP
#define AGEOFWAR_IACTION_HPP

#include <string>

// Base class for all actions. Actions are created by child classes of IBassUnit and sent back to Board to process them
class IAction {
public:
    //trivial destructor
    virtual ~IAction() = default;

    //Not used -> by having a virtual method we make this class purely virtual and block the possibility of initializing it
    virtual std::string getActionLog() = 0;
};

#endif //AGEOFWAR_IACTION_HPP