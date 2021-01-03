//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "Board.hpp"
#include "../units/Archer.hpp"

Board::Board(IPlayer *pPlayerOne, IPlayer *pPlayerTwo, int size) {
    _size = size;
    _boardData.insert(_boardData.begin(), size, nullptr);
    p_PlayerOne = pPlayerOne;
    p_PlayerTwo = pPlayerTwo;
    if (test != nullptr) {
        delete[] test;
        test = nullptr;
    }
    if (test == nullptr) {
        test = new int[size];
        if (test == nullptr) {
            std::cout << "ERROR" << std::endl;
        } else {
            std::cout << "Array was created succesfully" << std::endl;
        }
    }
}
Board::~Board() {
    std::vector<IBaseUnit *>().swap(_boardData);
}

vector<IBaseUnit *> Board::getPlayerUnits(IPlayer *owner, bool isEnemyBaseDirection) {
    vector<IBaseUnit *> result = {};
    if ((owner->GetNumber() == 1 && isEnemyBaseDirection) || (owner->GetNumber() == 2 && !isEnemyBaseDirection)) {
        for (auto &i : _boardData) {
            if (i != nullptr && i->IsOwnedBy(owner)) {
                result.push_back(i);
            }
        }
    } else if ((owner->GetNumber() == 1 && !isEnemyBaseDirection) ||
               (owner->GetNumber() == 2 && isEnemyBaseDirection)) {
        for (int i = _boardData.size() - 1; i >= 0; i--) {
            if (_boardData[i] != nullptr && _boardData[i]->IsOwnedBy(owner)) {
                result.push_back(_boardData[i]);
            }
        }
    }

    return result;
}

void Board::addUnit(IBaseUnit *unit, IPlayer *player) {
    if (player->GetNumber() == 1 && _boardData[0] == nullptr) {
        _boardData[0] = unit;
    }
    if (player->GetNumber() == 2 && _boardData[_size - 1] == nullptr) {
        _boardData[_size - 1] = unit;
    }
}

void Board::moveUnitForward(IBaseUnit *unit, int count) {
    int unitPosition = findUnitPosition(unit);
    int direction = unit->GetPlayer()->GetNumber() == 1 ? 1 : -1;
    int newIndex = unitPosition + count * direction;

    if (newIndex <= 0 || newIndex >= _size - 1) return;

    if (_boardData[newIndex] == nullptr) {
        _boardData[newIndex] = unit;
        _boardData[unitPosition] = nullptr;
    }
}

int Board::findUnitPosition(IBaseUnit *unit) {
    if (unit == nullptr) return -1;
    for (int i = 0; i < _boardData.size(); ++i) {
        if (_boardData[i] == unit) {
            return i;
        }
    }
    return -1;
}


vector<int> Board::getDistancesToEnemies(IBaseUnit *pUnit) {
    vector<int> result;
    int unitPosition = findUnitPosition(pUnit);
    IPlayer *unitOwner = pUnit->GetPlayer();

    //For Player One
    if (pUnit->GetPlayer()->GetNumber() == 1) {
        for (int i = 0; i < _boardData.size(); ++i) {
            //Add the base to the vector
            if (i == _boardData.size() - 1) {
                result.push_back(getDistanceValueFromIndexes(_boardData.size() - 1, unitPosition));
            }
            if (_boardData[i] != nullptr && !_boardData[i]->IsOwnedBy(unitOwner)) {
                result.push_back(getDistanceValueFromIndexes(i, unitPosition));
            }
        }
    } else { //Player Two
        for (int i = _boardData.size() - 1; i >= 0; --i) {
            //Add the base to the vector
            if (i == 0) {
                result.push_back(getDistanceValueFromIndexes(0, unitPosition));
            }
            if (_boardData[i] != nullptr && !_boardData[i]->IsOwnedBy(unitOwner)) {
                result.push_back(getDistanceValueFromIndexes(i, unitPosition));
            }
        }
    }


    return result;
}

int Board::getDistanceValueFromIndexes(int index1, int index2) {
    return abs(index1 - index2);
}

void Board::attackRelativePositions(IBaseUnit *pUnit, std::vector<int> attackedPositions) {
    int unitPosition = findUnitPosition(pUnit);
    int direction = pUnit->GetPlayer()->GetNumber() == 1 ? 1 : -1;
    for (int i = 0; i < attackedPositions.size(); ++i) {
        int tempUnitPosition = unitPosition + direction * attackedPositions[i];
        IBaseUnit *tempUnit = _boardData[tempUnitPosition];
        if (tempUnit != nullptr) {
            tempUnit->GetDamage(pUnit->GetAttackPower());
            std::cout << "Unit at " << unitPosition << " attacked enemy unit at "
                      << tempUnitPosition << " HP left:" << tempUnit->GetHp() << std::endl;
            if (tempUnit->GetHp() <= 0) {
                delete tempUnit;
                _boardData[tempUnitPosition] = nullptr;
                std::cout << "Unit killed!\n";
            }
        }
        else{
            if(tempUnitPosition == 0){
                p_PlayerOne->GetBase()->GetDamage(pUnit->GetAttackPower());
                std::cout << "Player One Base HP: " << p_PlayerOne->GetBase()->GetHp() << std::endl;
            }
            if(tempUnitPosition == _size - 1){
                p_PlayerTwo->GetBase()->GetDamage(pUnit->GetAttackPower());
                std::cout << "Player Two Base HP: " << p_PlayerTwo->GetBase()->GetHp() << std::endl;
            }
        }
    }
}




