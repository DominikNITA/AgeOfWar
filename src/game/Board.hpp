//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include "../units/IBaseUnit.hpp"

using std::vector;

class Board {
public:
    //General
    Board(int size = 12);
    ~Board();
    //Methods
    vector<IBaseUnit*> getPlayerUnits(IPlayer* owner, bool isEnemyBaseDirection);
    void addUnit(IBaseUnit* unit, IPlayer* player);
    void moveUnitForward(IBaseUnit* unit, int count);
    int findUnitPosition(IBaseUnit* unit);
    vector<int> getDistancesToEnemies(IBaseUnit* pUnit);
private:
    //Variables
    int _size;
    vector<IBaseUnit*> _boardData;
    int* test = nullptr;
    //Methods
    int getDistanceValueFromIndexes(int index1, int index2);
};


#endif //AGEOFWAR_BOARD_HPP
