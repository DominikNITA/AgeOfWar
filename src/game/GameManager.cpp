//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include <memory>
#include <fstream>
#include "GameManager.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"
#include "actions/ActionAttack.hpp"
#include "actions/ActionNone.hpp"
#include "actions/ActionMove.hpp"
#include "../utility/Helper.hpp"
//#include "../libs/cereal/archives/xml.hpp"
//#include "../libs/cereal/cereal.hpp"
#include <cereal/cereal.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>

GameManager::GameManager(int mode, std::string name) : m_mode(mode), m_name(name) {
    m_currentRound = 0;
    p_gameLogger.reset(new GameLogger());

    std::string playerName;

    std::cout << " First player nick: ";
    std::cin >> playerName;
    Helper::erasePreviousLine();
    p_playerOne.reset(new HumanPlayer(1, playerName, p_gameLogger));
    if (m_mode == 2) {
        std::cout << " Second player nick: ";
        std::cin >> playerName;
        Helper::erasePreviousLine();
        p_playerTwo.reset(new HumanPlayer(2, playerName, p_gameLogger));
    } else {
        p_playerTwo.reset(new ComputerPlayer(2, p_gameLogger));
    }

    p_board.reset(new Board(p_playerOne, p_playerTwo, p_gameLogger, m_boardSize));

    initializeBuyingManager();
}

void GameManager::initializeBuyingManager() {
    p_buyingManager.reset(new BuyingManager());
    p_buyingManager->addUnit("fantassin", 10, new UnitFactory<Fantassin>);
    p_buyingManager->addUnit("archer", 12, new UnitFactory<Archer>);
    p_buyingManager->addUnit("catapult", 20, new UnitFactory<Catapult>);
}


GameManager::~GameManager() {
//    if(p_playerOne != nullptr){
//        delete p_playerOne;
//        p_playerOne = nullptr;
//    }
//    if(p_playerTwo != nullptr){
//        delete p_playerTwo;
//        p_playerTwo = nullptr;
//    }
//    if(p_board != nullptr){
//        delete p_board;
//        p_board = nullptr;
//    }
//    delete p_buyingManager;
}

void GameManager::startGame() {

    p_board->draw();

    gameLoop();
}

void GameManager::gameLoop() {
    while ((m_currentRound < m_roundLimit) && !m_isFinished) {
        m_currentRound++;
        nextRound();
    }
    p_gameLogger->logAndDraw(Helper::getColorString(YELLOW) + "Game has finished!");
    int temp;
    if (m_currentRound == m_roundLimit) {
        p_gameLogger->logAndDraw(Helper::getColorString(BLUE) + "It's a draw: maximum amount of rounds passed!");
        std::cin >> temp;
        return;
    }
    if (p_playerOne->getBase()->GetHp() <= 0) {
        p_gameLogger->logAndDraw(
                Helper::getColorString(p_playerTwo->getColorCode()) + p_playerTwo->getName() + " won the game!");
        std::cin >> temp;
        return;
    } else {
        p_gameLogger->logAndDraw(
                Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName() + " won the game!");
        std::cin >> temp;
        return;
    }
}

void GameManager::nextRound() {
    p_gameLogger->log(
            Helper::getColorString(BLUE) + Helper::getColorString(BOLD) + "Round " + std::to_string(m_currentRound) +
            ":");

    //1.Give currency to both players
    p_playerOne->addCurrency(8);
    p_playerTwo->addCurrency(8);
    p_gameLogger->log("Both players received "
                      + Helper::getColorString(YELLOW) + std::to_string(8) + " coins.");

    //2. Player One turn
    p_gameLogger->log(Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName()
                                                    + Helper::getColorString(RESET)  + " turn:");
    redrawAll();
    playTurn(p_playerOne);
    p_gameLogger->draw();

    //3. Player Two turn
    p_gameLogger->logAndDraw(Helper::getColorString(p_playerTwo->getColorCode())+ p_playerTwo->getName()
                                                    + Helper::getColorString(RESET)  + " turn:");
    p_gameLogger->draw();
    playTurn(p_playerTwo);

    //4.Save state
    saveState();
}

void GameManager::playTurn(std::shared_ptr<IPlayer> pPlayer) {

    //Make Action 1
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 1 Phase");
    p_board->doActions(1, pPlayer);
    if (m_isFinished) return;

    //Make Action 2
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 2 Phase");
    p_board->doActions(2, pPlayer);
    if (m_isFinished) return;

    //Make Action 3
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 3 Phase");
    p_board->doActions(3, pPlayer);
    p_gameLogger->draw();

    if (m_isFinished) return;
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Buying Phase");
    if (p_board->canPlayerAddUnit(*pPlayer)) {
        if (p_buyingManager->getMinimalPrice() <= pPlayer->getCurrency()) {

            int choice = pPlayer->chooseUnitToBuy(p_buyingManager->getPurchasableUnits());
            auto unitToBuy = p_buyingManager->returnUnit(choice);
            unitToBuy->setOwner(pPlayer);
            p_board->addUnit(unitToBuy, pPlayer);
        } else {
            p_gameLogger->log(Helper::getColorString(pPlayer->getColorCode())+ pPlayer->getName()
                                     + Helper::getColorString(RESET) + " has not enough "+ Helper::getColorString(YELLOW)+"coins"+ Helper::getColorString(RESET)+" to buy any unit. Skipping buying phase...");
        }
    } else {
        p_gameLogger->log(Helper::getColorString(pPlayer->getColorCode())+ pPlayer->getName()
                                 + Helper::getColorString(RESET) + " cannot buy units because his base is occupied");
    }
    redrawAll();
    Helper::Sleep(1500);
}

void GameManager::redrawAll() {
    p_gameLogger->clear();
    p_board->clear();
    p_board->draw();
    p_gameLogger->draw();
}

void GameManager::saveState() {
    std::ofstream os("saves/" + m_name + ".xml");
    cereal::XMLOutputArchive archive(os);
    archive(*this);
}