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
    Board(int size = 12);
    ~Board();
    vector<IBaseUnit*> getPlayerUnits(IPlayer* owner, bool isEnemyBaseDirection);
    void AddUnit(IBaseUnit* unit, IPlayer* player);
    void MoveUnitForward(IBaseUnit* unit, int count);
    int FindUnitPosition(IBaseUnit* unit);
private:
    int _size;
    vector<IBaseUnit*> _boardData;
    int* test = nullptr;
};


#endif //AGEOFWAR_BOARD_HPP
