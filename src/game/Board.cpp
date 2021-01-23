//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "Board.hpp"
#include "../units/Archer.hpp"
#include "../utility/Helper.hpp"
#include "../units/Fantassin.hpp"
#include "../units/SuperSoldier.hpp"

Board::Board(std::shared_ptr<IPlayer> pPlayerOne, std::shared_ptr<IPlayer> pPlayerTwo, GameLogger *pGameLogger, int size) {
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

vector<IBaseUnit *> Board::getPlayerUnits(std::shared_ptr<IPlayer> owner, bool isEnemyBaseDirection) {
    vector<IBaseUnit *> result = {};
    if ((owner->getNumber() == 1 && isEnemyBaseDirection) || (owner->getNumber() == 2 && !isEnemyBaseDirection)) {
        for (auto &i : _boardData) {
            if (i != nullptr && i->isOwnedBy(owner)) {
                result.push_back(i);
            }
        }
    } else if ((owner->getNumber() == 1 && !isEnemyBaseDirection) ||
               (owner->getNumber() == 2 && isEnemyBaseDirection)) {
        for (int i = _boardData.size() - 1; i >= 0; i--) {
            if (_boardData[i] != nullptr && _boardData[i]->isOwnedBy(owner)) {
                result.push_back(_boardData[i]);
            }
        }
    }

    return result;
}

void Board::addUnit(IBaseUnit *unit, std::shared_ptr<IPlayer> player) {
    if (player->getNumber() == 1 && _boardData[0] == nullptr) {
        _boardData[0] = unit;
    }
    if (player->getNumber() == 2 && _boardData[_size - 1] == nullptr) {
        _boardData[_size - 1] = unit;
    }
}

void Board::moveUnitForward(IBaseUnit *unit, int count) {
    int unitPosition = findUnitPosition(unit);
    int direction = unit->getOwner()->getNumber() == 1 ? 1 : -1;
    int newIndex = unitPosition + count * direction;

    if (newIndex <= 0 || newIndex >= _size - 1) return;

    if (_boardData[newIndex] == nullptr) {
        _boardData[newIndex] = unit;
        _boardData[unitPosition] = nullptr;
        p_gameLogger->logAndDraw(
                "Moving unit " + Helper::getColorString(unit->getOwner()->getColorCode()) + unit->print() +
                Helper::getColorString(RESET) + " from " + Helper::getColorString(BLUE) + std::to_string(unitPosition) +
                Helper::getColorString(RESET) + " to " + Helper::getColorString(BLUE) + std::to_string(newIndex));
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
    std::shared_ptr<IPlayer> unitOwner = pUnit->getOwner();

    //For Player One
    if (pUnit->getOwner()->getNumber() == 1) {
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
    Fantassin *pThisFantassin;

    //General variables
    int unitPosition = findUnitPosition(pUnit);
    int direction = pUnit->getOwner()->getNumber() == 1 ? 1 : -1;

    for (int i = 0; i < attackedPositions.size(); ++i) {
        int targetUnitPosition = unitPosition + direction * attackedPositions[i];
        IBaseUnit *pTargetUnit = _boardData[targetUnitPosition];
        if (pTargetUnit != nullptr) {
            pTargetUnit->ReceiveDamage(pUnit->GetAttackPower());
            p_gameLogger->log(
                    "Unit " + getUnitStringWithPosition(pUnit, unitPosition) + " attacked enemy unit " +
                    getUnitStringWithPosition(pTargetUnit, targetUnitPosition));
            //Enemy unit died
            if (pTargetUnit->GetHp() <= 0) {
                if (pTargetUnit->getOwner() == pUnit->getOwner()) {
                    //Heal unit back to 1 hp
                    pTargetUnit->ReceiveDamage(-(pTargetUnit->GetHp() - 1));
                    p_gameLogger->log(Helper::getColorString(BRIGHTCYAN) + "Unit " +
                                      getUnitStringWithPosition(pTargetUnit, targetUnitPosition) +
                                      Helper::getColorString(BRIGHTCYAN) +
                                      " got saved from friendly fire by God's Shield.");
                } else {
                    p_gameLogger->log(Helper::getColorString(RED) + "Unit " +
                                      getUnitStringWithPosition(pTargetUnit, targetUnitPosition) +
                                      Helper::getColorString(RED) + " got killed and enemy is rewarded with " +
                                      Helper::getColorString(YELLOW) +
                                      std::to_string(pTargetUnit->GetKillReward()) +
                                      " coins" + Helper::getColorString(RESET) + "!");
                    //Add coins for the player
                    pUnit->getOwner()->addCurrency(pTargetUnit->GetKillReward());

                    //Deal with special case for Fantassin
                    if ((pThisFantassin = dynamic_cast<Fantassin *>(pUnit))) {
                        if (auto pEnemyFantassin = dynamic_cast<Fantassin *>(pTargetUnit)) {
                            p_gameLogger->log(
                                    "Unit " + getUnitStringWithPosition(pUnit, unitPosition) + " is upgraded to " +
                                    Helper::getColorString(YELLOW) + "SuperSoldier!");
                            pThisFantassin->upgradeToSuperSoldier();
                        }
                    }
                    //Remove enemy unit from the board
                    delete pTargetUnit;
                    pTargetUnit = nullptr;
                    _boardData[targetUnitPosition] = nullptr;
                }
            }
            p_gameLogger->draw();
        } else {
            if (targetUnitPosition == 0) {
                p_PlayerOne->getBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw("Base got attacked");
            }
            if (targetUnitPosition == _size - 1) {
                p_PlayerTwo->getBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw("Base got attacked");
            }
        }
    }
}

bool Board::canPlayerAddUnit(std::shared_ptr<IPlayer> player) {
    if (player->getNumber() == 1) {
        return _boardData[0] == nullptr;
    } else {
        return _boardData[_size - 1] == nullptr;
    }
}

void Board::draw() {
    for (int i = 0; i < _boardData.size(); ++i) {
        if (_boardData[i] != nullptr) {
            std::cout << " ";
            Helper::setColor(_boardData[i]->getOwner()->getColorCode());
            _boardData[i]->draw();
            std::cout << "  ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
    Helper::setColor(RESET);
    for (int i = 0; i < _boardData.size(); ++i) {
        std::cout << "――― ";
    }
    std::cout << std::endl;
    for (int i = 0; i < _boardData.size(); ++i) {
        if (_boardData[i] != nullptr) {
            if (_boardData[i]->GetHp() < 5) {
                Helper::setColor(RED);
            } else {
                Helper::setColor(RESET);
            }
            std::cout << " " << _boardData[i]->GetHp();

            if (_boardData[i]->GetHp() < 10) std::cout << " ";

            std::cout << " ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
}

void Board::clear() {
    for (int i = 0; i < 3; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
}

std::string Board::getUnitStringWithPosition(IBaseUnit *unit, int position) {
    return Helper::getColorString(unit->getOwner()->getColorCode()) + unit->print() +
           std::to_string(position) + Helper::getColorString(RESET);

}




