//
// Created by Dominik on 12/29/2020.
//

#ifndef AGEOFWAR_ACTIONMOVE_HPP
#define AGEOFWAR_ACTIONMOVE_HPP


#include <utility>

#include "IAction.hpp"
#include "../../units/IBaseUnit.hpp"

/// Action describing movement of an unit by a specified amount of blocks
class ActionMove : public IAction{
public:
    /// Action move constructor
    /// \param unit Source unit wanting to move forward
    /// \param count Amount of blocks to move forward (basically one for standard units)
    ActionMove(std::shared_ptr<IBaseUnit> unit, int count) : m_unit(std::move(unit)), m_count(count) {}

    /// Not used
    std::string GetActionLog() override;

    /// Getter for source unit
    /// \return Source unit wanting to move forward
    std::shared_ptr<IBaseUnit>getUnit() const;

    /// Getter for amount of blocks to move
    /// \return
    int getCount() const;

private:
    std::shared_ptr<IBaseUnit> m_unit;
    int m_count;
};


#endif //AGEOFWAR_ACTIONMOVE_HPP