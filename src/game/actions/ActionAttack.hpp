#ifndef AGEOFWAR_ACTIONATTACK_HPP
#define AGEOFWAR_ACTIONATTACK_HPP


#include "IAction.hpp"
#include "../../units/IAttacking.hpp"
#include <memory>
#include <utility>

/// Action describing attacking of blocks
class ActionAttack : public IAction {
public:
    /// Action attack constructor
    /// \param attacker
    /// \param attackedPositions
    ActionAttack(std::shared_ptr<IAttacking> attacker, std::vector<int> attackedPositions) : _attacker(
            std::move(attacker)), _attackedPositions(std::move(attackedPositions)) {}

    /// Getter for source unit
    /// \return Source unit wanting to attack
    std::shared_ptr<IAttacking> getAttacker() { return _attacker; }

    /// Getter for attacked positions relating to source unit position
    /// \return
    std::vector<int> getAttackedPositions() { return _attackedPositions; }

    //Not used
    std::string getActionLog() override { return "Attack"; };

private:
    std::shared_ptr<IAttacking> _attacker; //Source unit
    std::vector<int> _attackedPositions; // Attacked positions relating to source unit position
};


#endif //AGEOFWAR_ACTIONATTACK_HPP
