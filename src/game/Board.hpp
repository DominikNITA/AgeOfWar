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
    Board(std::shared_ptr<IPlayer> pPlayerOne,std::shared_ptr<IPlayer> pPlayerTwo, std::shared_ptr<GameLogger> pGameLogger,int size = 12);
    Board() { m_boardData.insert(m_boardData.begin(), 12, nullptr); };
    ~Board();

    //Methods
    void doActions(int actionNumber, std::shared_ptr<IPlayer> pPlayer);
    vector<std::shared_ptr<IBaseUnit>> getPlayerUnits(std::shared_ptr<IPlayer> pOwner, bool isEnemyBaseDirection);
    void addUnit(std::shared_ptr<IBaseUnit> pUnit, std::shared_ptr<IPlayer> player);
    void moveUnitForward(std::shared_ptr<IBaseUnit> pUnit, int count);
    int findUnitPosition(std::shared_ptr<IBaseUnit> pUnit);
    vector<int> getDistancesToEnemies(std::shared_ptr<IBaseUnit> pUnit);
    void attackRelativePositions(std::shared_ptr<IBaseUnit> pUnit, std::vector<int> attackedPositions);

    //CHECKING STATE
    bool canPlayerAddUnit(const IPlayer& player);
    bool isOneBaseDestroyed();

    //DRAWING TO THE CONSOLE
    void updateView();
    void draw();
    void clear();

private:
    //Variables
    int m_size;
    vector<std::shared_ptr<IBaseUnit>> m_boardData;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;
    //Methods
    void doAction(IAction* pAction);
    int getDistanceValueFromIndexes(int index1, int index2);
    std::string getUnitStringWithPosition(std::shared_ptr<IBaseUnit> unit, int position);

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_size), CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo), CEREAL_NVP(p_gameLogger));
    }
};


#endif //AGEOFWAR_BOARD_HPP
