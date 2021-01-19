//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "Board.hpp"
#include "../units/Archer.hpp"
#include "../utility/ConsoleHelper.hpp"
#include "../units/Fantassin.hpp"
#include "../units/SuperSoldier.hpp"

Board::Board(IPlayer *pPlayerOne, IPlayer *pPlayerTwo, GameLogger *pGameLogger, int size) {
    _size = size;
    _boardData.insert(_boardData.begin(), size, nullptr);
    p_PlayerOne = pPlayerOne;
    p_PlayerTwo = pPlayerTwo;
    p_gameLogger = pGameLogger;
//    CREATION TESTS
//    if (test != nullptr) {
//        delete[] test;
//        test = nullptr;
//    }
//    if (test == nullptr) {
//        test = new int[size];
//        if (test == nullptr) {
//            std::cout << "ERROR" << std::endl;
//        } else {
//            std::cout << "Array was created succesfully" << std::endl;
//        }
//    }
}

Board::~Board() {
    for (auto p : _boardData) {
        delete p;
    }
    _boardData.clear();
//    std::vector<IBaseUnit *>().swap(_boardData);
}

vector<IBaseUnit *> Board::getPlayerUnits(IPlayer *owner, bool isEnemyBaseDirection) {
    vector<IBaseUnit *> result = {};
    if ((owner->GetNumber() == 1 && isEnemyBaseDirection) || (owner->GetNumber() == 2 && !isEnemyBaseDirection)) {
        for (auto &i : _boardData) {
            if (i != nullptr && i->isOwnedBy(owner)) {
                result.push_back(i);
            }
        }
    } else if ((owner->GetNumber() == 1 && !isEnemyBaseDirection) ||
               (owner->GetNumber() == 2 && isEnemyBaseDirection)) {
        for (int i = _boardData.size() - 1; i >= 0; i--) {
            if (_boardData[i] != nullptr && _boardData[i]->isOwnedBy(owner)) {
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
    int direction = unit->getOwner()->GetNumber() == 1 ? 1 : -1;
    int newIndex = unitPosition + count * direction;

    if (newIndex <= 0 || newIndex >= _size - 1) return;

    if (_boardData[newIndex] == nullptr) {
        _boardData[newIndex] = unit;
        _boardData[unitPosition] = nullptr;
        p_gameLogger->logAndDraw("Moving unit " + ConsoleHelper::getColorString(unit->getOwner()->getColorCode()) + unit->print() + ConsoleHelper::getColorString(RESET) + " from "+ ConsoleHelper::getColorString(BLUE) +std::to_string(unitPosition) + ConsoleHelper::getColorString(RESET) + " to "+ ConsoleHelper::getColorString(BLUE)+std::to_string(newIndex));
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
    IPlayer *unitOwner = pUnit->getOwner();

    //For Player One
    if (pUnit->getOwner()->GetNumber() == 1) {
        for (int i = 0; i < _boardData.size(); ++i) {
            //Add the base to the vector
            if (i == _boardData.size() - 1) {
                result.push_back(getDistanceValueFromIndexes(_boardData.size() - 1, unitPosition));
            } else if (_boardData[i] != nullptr && !_boardData[i]->isOwnedBy(unitOwner)) {
                result.push_back(getDistanceValueFromIndexes(i, unitPosition));
            }
        }
    } else { //Player Two
        for (int i = _boardData.size() - 1; i >= 0; --i) {
            //Add the base to the vector
            if (i == 0) {
                result.push_back(getDistanceValueFromIndexes(0, unitPosition));
            } else if (_boardData[i] != nullptr && !_boardData[i]->isOwnedBy(unitOwner)) {
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
    //Variables for upgrading fantassin to super soldier
    bool isUpgradedToSuperSoldier = false;
    Fantassin *pThisFantassin;

    //General variables
    int unitPosition = findUnitPosition(pUnit);
    int direction = pUnit->getOwner()->GetNumber() == 1 ? 1 : -1;

    for (int i = 0; i < attackedPositions.size(); ++i) {
        int targetUnitPosition = unitPosition + direction * attackedPositions[i];
        IBaseUnit *pTargetUnit = _boardData[targetUnitPosition];
        if (pTargetUnit != nullptr) {
            pTargetUnit->ReceiveDamage(pUnit->GetAttackPower());
            p_gameLogger->log(
                    "Unit " + ConsoleHelper::getColorString(pUnit->getOwner()->getColorCode()) + pUnit->print() +
                    std::to_string(unitPosition) + ConsoleHelper::getColorString(RESET) + " attacked enemy unit " +
                    ConsoleHelper::getColorString(pTargetUnit->getOwner()->getColorCode()) + pTargetUnit->print() +
                    std::to_string(targetUnitPosition));
            //Enemy unit died
            if (pTargetUnit->GetHp() <= 0) {
                p_gameLogger->log(ConsoleHelper::getColorString(RED) + "Unit " +
                                  ConsoleHelper::getColorString(pTargetUnit->getOwner()->getColorCode()) +
                                  pTargetUnit->print() + std::to_string(targetUnitPosition) +
                                  ConsoleHelper::getColorString(RED) + " got killed and enemy is rewarded with " +
                                  ConsoleHelper::getColorString(YELLOW) + std::to_string(pTargetUnit->GetKillReward()) +
                                  " coins" + ConsoleHelper::getColorString(RESET) + "!");
                //Add coins for the player
                pUnit->getOwner()->addCurrency(pTargetUnit->GetKillReward());

                //Deal with special case for Fantassin
                if ((pThisFantassin = dynamic_cast<Fantassin *>(pUnit))) {
                    if (auto pEnemyFantassin = dynamic_cast<Fantassin *>(pTargetUnit)) {
                        isUpgradedToSuperSoldier = true;
                    }
                }
                //Remove enemy unit from the board
                delete pTargetUnit;
                _boardData[targetUnitPosition] = nullptr;
                p_gameLogger->draw();
            }
        } else {
            if (targetUnitPosition == 0) {
                p_PlayerOne->GetBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw("Base got attacked");
            }
            if (targetUnitPosition == _size - 1) {
                p_PlayerTwo->GetBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw("Base got attacked");
            }
        }
    }

    if (isUpgradedToSuperSoldier) {
        SuperSoldier superSoldier = *pThisFantassin;
        p_gameLogger->log(
                "Unit " + ConsoleHelper::getColorString(pUnit->getOwner()->getColorCode()) + pUnit->print() +
                std::to_string(unitPosition) + ConsoleHelper::getColorString(RESET) + " is upgraded to " +
                ConsoleHelper::getColorString(YELLOW) + "SuperSoldier!" + ConsoleHelper::getColorString(RED) + "Not completely implemented :(");

//        delete pUnit;
//        _boardData[unitPosition] = nullptr;
//        _boardData[unitPosition] = &superSoldier;
    }
}

bool Board::canPlayerAddUnit(IPlayer *player) {
    if (player->GetNumber() == 1) {
        return _boardData[0] == nullptr;
    } else {
        return _boardData[_size - 1] == nullptr;
    }
}

void Board::draw() {
    for (int i = 0; i < _boardData.size(); ++i) {
        if (_boardData[i] != nullptr) {
            std::cout << " ";
            ConsoleHelper::setColor(_boardData[i]->getOwner()->getColorCode());
            _boardData[i]->draw();
            std::cout << "  ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
    ConsoleHelper::setColor(RESET);
    for (int i = 0; i < _boardData.size(); ++i) {
        std::cout << "___ ";
    }
    std::cout << std::endl;
    for (int i = 0; i < _boardData.size(); ++i) {
        if (_boardData[i] != nullptr) {
            if (_boardData[i]->GetHp() < 5) {
                ConsoleHelper::setColor(RED);
            } else {
                ConsoleHelper::setColor(RESET);
            }
            std::cout << " ";
            _boardData[i]->draw();
            std::cout << "  ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
}




