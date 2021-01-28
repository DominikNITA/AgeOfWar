//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include <utility>
#include "Board.hpp"
#include "../units/Fantassin.hpp"
#include "actions/ActionMove.hpp"
#include "actions/ActionAttack.hpp"
#include "actions/ActionNone.hpp"

Board::Board(std::shared_ptr<IPlayer> pPlayerOne, std::shared_ptr<IPlayer> pPlayerTwo, std::shared_ptr<GameLogger> pGameLogger, int size) {
    m_size = size;
    m_boardData.insert(m_boardData.begin(), size, nullptr);
    p_playerOne = std::move(pPlayerOne);
    p_playerTwo = std::move(pPlayerTwo);
    p_gameLogger = std::move(pGameLogger);
}

Board::~Board() {
//    for (auto p : m_boardData) {
//        delete p;
//    }
    m_boardData.clear();
//    std::vector<IBaseUnit *>().swap(m_boardData);
}

void Board::doActions(int actionNumber, const std::shared_ptr<IPlayer>& pPlayer) {
    auto units = getPlayerUnits(pPlayer, actionNumber == 1);
    if(units.empty()){
        p_gameLogger->logAndDraw(Helper::getColorString(pPlayer->getColorCode())+ pPlayer->getName()
        + Helper::getColorString(RESET) + " has no units!");
    }
    for (auto & unit : units) {
        //Catapult could kill it's own unit before it's turn -> Segmentation fault
//        if(units[i] == nullptr) continue;
        auto action = unit->getAction(actionNumber, getDistancesToEnemies(unit), unit);
        doAction(action);
        if(isOneBaseDestroyed()){
            break;
        }
        Helper::Sleep(150);
        updateView();
    }
    Helper::Sleep(300);
}

void Board::doAction(IAction *pAction) {
    if(pAction == nullptr){
        std::cout << "Null action pointer\n";
        return;
    }
    if(auto pMoveAction = dynamic_cast<ActionMove*>(pAction)){
        moveUnitForward(pMoveAction->getUnit(), pMoveAction->getCount());
    }
    else if(auto pAttackAction = dynamic_cast<ActionAttack*>(pAction)){
        attackRelativePositions(std::dynamic_pointer_cast<IBaseUnit>(pAttackAction->GetAttacker()), pAttackAction->GetAttackedPositions());
    }
    else if (dynamic_cast<ActionNone*>(pAction) != nullptr) {
        /*std::cout << "Nothing todo!\n";*/
    }
    else{
        std::cout << "ERROR: unknown action type: " << pAction->GetActionLog() << std::endl;
    }
}

vector<std::shared_ptr<IBaseUnit>> Board::getPlayerUnits(const std::shared_ptr<IPlayer>& owner, bool isEnemyBaseDirection) {
    vector<std::shared_ptr<IBaseUnit>> result = {};
    if ((owner->getNumber() == 1 && isEnemyBaseDirection) || (owner->getNumber() == 2 && !isEnemyBaseDirection)) {
        for (auto & i : m_boardData) {
            if (i != nullptr && i->isOwnedBy(owner)) {
                result.push_back(i);
            }
        }
    } else if ((owner->getNumber() == 1 && !isEnemyBaseDirection) ||
               (owner->getNumber() == 2 && isEnemyBaseDirection)) {
        for (int i = m_size - 1; i >= 0; i--) {
            if (m_boardData[i] != nullptr && m_boardData[i]->isOwnedBy(owner)) {
                result.push_back(m_boardData[i]);
            }
        }
    }
    return result;
}

void Board::addUnit(const std::shared_ptr<IBaseUnit>& unit, const std::shared_ptr<IPlayer>& player) {
    if (player->getNumber() == 1 && m_boardData[0] == nullptr) {
        m_boardData[0] = unit;
    }
    if (player->getNumber() == 2 && m_boardData[m_size - 1] == nullptr) {
        m_boardData[m_size - 1] = unit;
    }
}

void Board::moveUnitForward(const std::shared_ptr<IBaseUnit>& unit, int count) {
    int unitPosition = findUnitPosition(unit);
    int direction = unit->getOwner()->getNumber() == 1 ? 1 : -1;
    int newIndex = unitPosition + count * direction;

    //bloque acces au cases contenant les bases
    if (newIndex <= 0 || newIndex >= m_size - 1) return;

    if (m_boardData[newIndex] == nullptr) {
        m_boardData[newIndex] = unit;
        m_boardData[unitPosition] = nullptr;
        p_gameLogger->logAndDraw(
                "Moving unit " + Helper::getColorString(unit->getOwner()->getColorCode()) + unit->print() +
                Helper::getColorString(RESET) + " from " + Helper::getColorString(BLUE) + std::to_string(unitPosition) +
                Helper::getColorString(RESET) + " to " + Helper::getColorString(BLUE) + std::to_string(newIndex));
    }
}

int Board::findUnitPosition(const std::shared_ptr<IBaseUnit>& unit) {
    if (unit == nullptr) return -1;
    for (int i = 0; i < m_boardData.size(); ++i) {
        if (m_boardData[i] == unit) {
            return i;
        }
    }
    return -1;
}

vector<int> Board::getDistancesToEnemies(const std::shared_ptr<IBaseUnit>& pUnit) {
    vector<int> result;
    int unitPosition = findUnitPosition(pUnit);
    std::shared_ptr<IPlayer> unitOwner = pUnit->getOwner();

    //For Player One
    if (pUnit->getOwner()->getNumber() == 1) {
        for (int i = 0; i < m_boardData.size(); ++i) {
            //Add the base to the vector
            if (i == m_boardData.size() - 1) {
                result.push_back(getDistanceValueFromIndexes(m_size - 1, unitPosition));
            } else if (m_boardData[i] != nullptr && !m_boardData[i]->isOwnedBy(unitOwner)) {
                result.push_back(getDistanceValueFromIndexes(i, unitPosition));
            }
        }
    } else { //Player Two
        for (int i = m_size - 1; i >= 0; --i) {
            //Add the base to the vector
            if (i == 0) {
                result.push_back(getDistanceValueFromIndexes(0, unitPosition));
            } else if (m_boardData[i] != nullptr && !m_boardData[i]->isOwnedBy(unitOwner)) {
                result.push_back(getDistanceValueFromIndexes(i, unitPosition));
            }
        }
    }

    return result;
}

int Board::getDistanceValueFromIndexes(int index1, int index2) {
    return abs(index1 - index2);
}

void Board::attackRelativePositions(const std::shared_ptr<IBaseUnit>& pUnit, const std::vector<int>& attackedPositions) {
    //General variables
    int unitPosition = findUnitPosition(pUnit);
    int direction = pUnit->getOwner()->getNumber() == 1 ? 1 : -1;

    for (int attackedPosition : attackedPositions) {
        int targetUnitPosition = unitPosition + direction * attackedPosition;
        std::shared_ptr<IBaseUnit>pTargetUnit = m_boardData[targetUnitPosition];
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
                    if (auto pThisFantassin = std::dynamic_pointer_cast<Fantassin>(pUnit)) {
                        if (std::dynamic_pointer_cast<Fantassin>(pTargetUnit) != nullptr) {
                            p_gameLogger->log(
                                    "Unit " + getUnitStringWithPosition(pUnit, unitPosition) + " is upgraded to " +
                                    Helper::getColorString(YELLOW) + "SuperSoldier!");
                            pThisFantassin->upgradeToSuperSoldier();
                        }
                    }
                    //Remove enemy unit from the board
                    //delete pTargetUnit;
                    pTargetUnit = nullptr;
                    m_boardData[targetUnitPosition] = nullptr;
                }
            }
            p_gameLogger->draw();
        } else {
            if (targetUnitPosition == 0) {
                p_playerOne->getBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw(Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName() + Helper::getColorString(RED) +" base got attacked!");
            }
            if (targetUnitPosition == m_size - 1) {
                p_playerTwo->getBase()->ReceiveDamage(pUnit->GetAttackPower());
                p_gameLogger->logAndDraw(Helper::getColorString(p_playerTwo->getColorCode())+ p_playerTwo->getName()+ Helper::getColorString(RED) + " base got attacked!");
            }
        }
    }
}

// STATE CHECKING

bool Board::canPlayerAddUnit(const IPlayer& player) {
    if (player.getNumber() == 1) {
        return m_boardData[0] == nullptr;
    } else {
        return m_boardData[m_size - 1] == nullptr;
    }
}

bool Board::isOneBaseDestroyed() {
    return p_playerOne->getBase()->GetHp() <= 0 || p_playerTwo->getBase()->GetHp() <= 0;
}

// DRAWING TO THE CONSOLE

void Board::updateView(){
    p_gameLogger->clear();
    clear();
    draw();
    p_gameLogger->draw();
}

void Board::draw() {
    //print Players names with remaining coins
    std::cout << Helper::getColorString(p_playerOne->getColorCode())+ p_playerOne->getName() + Helper::getColorString(RESET) + " (" + Helper::getColorString(YELLOW) << p_playerOne->getCurrency() << Helper::getColorString(RESET) + ")" << std::endl;
    std::cout << Helper::getColorString(p_playerTwo->getColorCode())+ p_playerTwo->getName() + Helper::getColorString(RESET) + " (" + Helper::getColorString(YELLOW) << p_playerTwo->getCurrency() << Helper::getColorString(RESET) + ")" << std::endl;

    //print bases' health
    for (int i = 0; i < m_size; ++i) {
        if (i == 0) {
            std::cout << p_playerOne->getBase()->GetHp() << " ";
        }
        else if ( i == m_size -1) {
            std::cout << p_playerTwo->getBase()->GetHp() << " ";
        }
        else{
            std::cout << "    ";
        }
    }
    std::cout << std::endl;

    //print bases' roofs
    for (int i = 0; i < m_size; ++i) {
        if( i == 0 ) {
            Helper::setColor(p_playerOne->getColorCode());
            std::cout << "___ ";
        }
        else if(i == m_size -1){
            Helper::setColor(p_playerTwo->getColorCode());
            std::cout << "___ ";
        }
        else{
            std::cout << "    ";
        }
    }
    std::cout << std::endl;

    //print units and bases' walls
    for (int i = 0; i < m_size; ++i) {
        if( i == 0 || i == m_size -1){
            if( i== 0){
                Helper::setColor(p_playerOne->getColorCode());
            }
            else{
                Helper::setColor(p_playerTwo->getColorCode());
            }
            std::cout << "|";
            if(m_boardData[i] != nullptr){
                Helper::setColor(m_boardData[i]->getOwner()->getColorCode());
                std::cout << m_boardData[i]->print();
            }
            else{
                std::cout << " ";
            }
            if( i== 0){Helper::setColor(p_playerOne->getColorCode());}
            else{Helper::setColor(p_playerTwo->getColorCode());}
            std::cout << "| ";
        }
        else if (m_boardData[i] != nullptr) {
            std::cout << " ";
            Helper::setColor(m_boardData[i]->getOwner()->getColorCode());
            std::cout << m_boardData[i]->print();
            std::cout << "  ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;

    // print cases
    Helper::setColor(RESET);
    for (int i = 0; i < m_size; ++i) {
        std::cout << "――― ";
    }
    std::cout << std::endl;


    for (int i = 0; i < m_size; ++i) {
        if (m_boardData[i] != nullptr) {
            if (m_boardData[i]->GetHp() < 5) {
                Helper::setColor(RED);
            } else {
                Helper::setColor(RESET);
            }
            std::cout << " " << m_boardData[i]->GetHp();

            if (m_boardData[i]->GetHp() < 10) std::cout << " ";

            std::cout << " ";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
}

void Board::clear() {
    for (int i = 0; i < 7; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
}

std::string Board::getUnitStringWithPosition(const std::shared_ptr<IBaseUnit>&unit, int position) {
    return Helper::getColorString(unit->getOwner()->getColorCode()) + unit->print() +
           std::to_string(position) + Helper::getColorString(RESET);
}