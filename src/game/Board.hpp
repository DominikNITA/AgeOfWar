//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include <memory>
#include <cereal/types/vector.hpp>

#include "../units/IBaseUnit.hpp"
#include "GameLogger.hpp"

using std::vector;

class Board {
public:
    //General
    /// Constructor for new game
    /// \param pPlayerOne
    /// \param pPlayerTwo
    /// \param pGameLogger Global game logger
    /// \param size Size of the board
    Board(std::shared_ptr<IPlayer> pPlayerOne,std::shared_ptr<IPlayer> pPlayerTwo, std::shared_ptr<GameLogger> pGameLogger,int size = 12);

    /// Default constructor used for serialization
    Board() { m_boardData.insert(m_boardData.begin(), 12, nullptr);
    m_size = 12;};

    /// Destructor
    ~Board();

    //Methods
    /// Perform actions for all actions of specified player according to action phase
    /// \param actionNumber Phase number, normally between 1 and 3
    /// \param pPlayer Player who's units will do actions
    void doActions(int actionNumber, const std::shared_ptr<IPlayer>& pPlayer);

    /// Get players units in specified order
    /// \param pOwner
    /// \param isEnemyBaseDirection
    /// \return playes units in specified order
    vector<std::shared_ptr<IBaseUnit>> getPlayerUnits(const std::shared_ptr<IPlayer>& pOwner, bool isEnemyBaseDirection);

    ///
    /// \param pUnit
    /// \param player
    void addUnit(const std::shared_ptr<IBaseUnit>& pUnit, const std::shared_ptr<IPlayer>& player);

    /// Checks if specified player's base is empty and adding a new unit is possible
    /// \param player player which base has to be checked
    /// \return
    bool canPlayerAddUnit(const IPlayer& player);

    /// Used for determining game ending condition
    /// \return is at least one base destroyed
    bool isOneBaseDestroyed();

    //DRAWING TO THE CONSOLE

    /// Update board data. It also clears game logs and then redraw it's
    void updateView();

    /// Draw board and other info to the console
    void draw();

    /// Remove board display from console
    static void clear();

private:
    //Variables
    int m_size;
    vector<std::shared_ptr<IBaseUnit>> m_boardData;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;

    //Methods
    void doAction(IAction* pAction);
    static int getDistanceValueFromIndexes(int index1, int index2);
    static std::string getUnitStringWithPosition(const std::shared_ptr<IBaseUnit>& unit, int position);
    void moveUnitForward(const std::shared_ptr<IBaseUnit>& pUnit, int count);
    int findUnitPosition(const std::shared_ptr<IBaseUnit>& pUnit);
    vector<int> getDistancesToEnemies(const std::shared_ptr<IBaseUnit>& pUnit);
    void attackRelativePositions(const std::shared_ptr<IBaseUnit>& pUnit, const std::vector<int>& attackedPositions);

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_size), CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo), CEREAL_NVP(p_gameLogger), CEREAL_NVP(m_boardData));
    }
};


#endif //AGEOFWAR_BOARD_HPP
