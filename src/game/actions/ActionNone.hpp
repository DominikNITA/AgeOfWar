#ifndef AGEOFWAR_ACTIONNONE_HPP
#define AGEOFWAR_ACTIONNONE_HPP


#include "IAction.hpp"

class ActionNone : public IAction {
public:
    ActionNone() = default;

    std::string getActionLog() override { return "skipped his turn"; };
};


#endif //AGEOFWAR_ACTIONNONE_HPP