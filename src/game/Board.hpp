//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include "../units/IUnit.hpp"

class Board {
public:

private:
    int _size;
    IUnit* boardData[];
};


#endif //AGEOFWAR_BOARD_HPP
