//
// Created by Dominik on 12/28/2020.
//

#include "Board.hpp"
#include "../units/Archer.hpp"

Board::Board(int size) {
    _size = size;
    _boardData.insert(_boardData.begin(), size,nullptr);
}

vector<IUnit*> Board::getPlayerUnits(IPlayer *owner, bool isEnemyBaseDirection) {
    vector<IUnit*> result = {};
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

void Board::AddUnit(IUnit *unit, IPlayer *player) {
    if(player->GetNumber() == 1 && _boardData[0] == nullptr){
        _boardData[0] = unit;
    }
}


