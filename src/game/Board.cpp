//
// Created by Dominik on 12/28/2020.
//

#include "Board.hpp"
#include "../units/Archer.hpp"

Board::Board(int size) {
    _size = size;
    _boardData.insert(_boardData.begin(), size,nullptr);
}

vector<IUnit*> Board::getPlayersUnits(IPlayer *owner,  bool isEnemyBaseDirection) {
    vector<IUnit*> result = {};
    if(owner->GetNumber() == 1 && isEnemyBaseDirection){
        for (auto & i : _boardData) {
            if(i != nullptr && i->IsOwnedBy(owner)){
                result.push_back(i);
            }
        }
    }
    else{
        
    }
    return result;
}

void Board::AddUnit(IUnit *unit, IPlayer *player) {
    if(player->GetNumber() == 1 && _boardData[0] == nullptr){
        _boardData[0] = unit;
    }
}


