//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "Board.hpp"
#include "../units/Archer.hpp"

Board::Board(int size) {
    _size = size;
    _boardData.insert(_boardData.begin(), size,nullptr);
    if(test != nullptr) {
        delete[] test;
        test = nullptr;
    }
    if(test == nullptr) {
        test = new int[size];
        if(test == nullptr) {
            std::cout << "ERROR" << std::endl;
        }
        else {
            std::cout << "Array was created succesfully" << std::endl;
        }
    }
}

vector<IBaseUnit*> Board::getPlayerUnits(IPlayer *owner, bool isEnemyBaseDirection) {
    vector<IBaseUnit*> result = {};
    if((owner->GetNumber() == 1 && isEnemyBaseDirection) || (owner->GetNumber() == 2 && !isEnemyBaseDirection)) {
        for (auto &i : _boardData) {
            if (i != nullptr && i->IsOwnedBy(owner)) {
                result.push_back(i);
            }
        }
    }
    else if ((owner->GetNumber() == 1 && !isEnemyBaseDirection) || (owner->GetNumber() == 2 && isEnemyBaseDirection)) {
        for (int i = _boardData.size() - 1; i >= 0 ; i--) {
            if(_boardData[i] != nullptr && _boardData[i]->IsOwnedBy(owner)){
                    result.push_back(_boardData[i]);
                }
            }
        }

    return result;
}

void Board::AddUnit(IBaseUnit *unit, IPlayer *player) {
    if(player->GetNumber() == 1 && _boardData[0] == nullptr){
        _boardData[0] = unit;
    }
}

void Board::MoveUnitForward(IBaseUnit *unit, int count) {
    int unitPosition = FindUnitPosition(unit);
    int direction = unit->GetPlayer()->GetNumber() == 1 ? 1 : -1;
    int newIndex = unitPosition + count*direction;

    if(newIndex <= 0 || newIndex >= _size - 1) return;

    if(_boardData[newIndex] == nullptr){
        _boardData[newIndex] = unit;
        _boardData[unitPosition] = nullptr;
    }
}

int Board::FindUnitPosition(IBaseUnit *unit) {
    if (unit == nullptr) return -1;
    for (int i = 0; i < _boardData.size(); ++i) {
        if(_boardData[i] == unit){
            return i;
        }
    }
    return -1;
}

Board::~Board() {
    std::vector<IBaseUnit*>().swap(_boardData);
}
