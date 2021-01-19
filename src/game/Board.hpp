//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include "../units/IBaseUnit.hpp"
#include "GameLogger.hpp"

using std::vector;

class Board : public IDrawable {
public:
    //General
    Board(IPlayer* pPlayerOne,IPlayer* pPlayerTwo, GameLogger* pGameLogger,int size = 12);
    ~Board();
    //Methods
    vector<IBaseUnit*> getPlayerUnits(IPlayer* pOwner, bool isEnemyBaseDirection);
    void addUnit(IBaseUnit* pUnit, IPlayer* player);
    void moveUnitForward(IBaseUnit* pUnit, int count);
    int findUnitPosition(IBaseUnit* pUnit);
    vector<int> getDistancesToEnemies(IBaseUnit* pUnit);
    void attackRelativePositions(IBaseUnit* pUnit, std::vector<int> attackedPositions);
    bool canPlayerAddUnit(IPlayer* player);
    void draw() override;
    void clear();

private:
    //Variables
    int _size;
    vector<IBaseUnit*> _boardData;
    int* test = nullptr;
    IPlayer* p_PlayerOne;
    IPlayer* p_PlayerTwo;
    GameLogger* p_gameLogger;
    //Methods
    int getDistanceValueFromIndexes(int index1, int index2);
};


#endif //AGEOFWAR_BOARD_HPP
