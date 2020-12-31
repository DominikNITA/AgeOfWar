//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include "../units/IUnit.hpp"

using std::vector;

class Board {
public:
    Board(int size = 12);
    vector<IUnit*> getPlayerUnits(IPlayer* owner, bool isEnemyBaseDirection);
    void AddUnit(IUnit* unit, IPlayer* player);
private:
    int _size;
    vector<IUnit*> _boardData;
};


#endif //AGEOFWAR_BOARD_HPP
