#include <iostream>
#include <memory>
#include <fstream>
#include "GameManager.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"

GameManager::GameManager(int mode, std::string name) : m_mode(mode), m_name(std::move(name)) {
    m_currentRound = 0;
    p_gameLogger.reset(new GameLogger());

    // Temporary variable for storing players name
    std::string playerName;

    // Create first player
    std::cout << " First player nick: ";
    std::cin >> playerName;
    Helper::erasePreviousLine();
    p_playerOne.reset(new HumanPlayer(1, playerName, p_gameLogger));

    // Create second player
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

void GameManager::startGame() {
    // We have to draw board first for good display order
    p_board->draw();

    // Start main game loop
    gameLoop();
}

void GameManager::gameLoop() {
    // Check end game conditions and if not accomplished then continue the game
    while ((m_currentRound < m_roundLimit) && !p_board->isOneBaseDestroyed()) {
        m_currentRound++;
        nextRound();
    }

    // Show end game results
    p_gameLogger->logAndDraw(Helper::getColorString(YELLOW) + "Game has finished!");

    if (m_currentRound == m_roundLimit) {
        p_gameLogger->logAndDraw(Helper::getColorString(BLUE) + "It's a draw: maximum amount of rounds passed!");
    } else if (p_playerOne->getBase()->GetHp() <= 0) {
        p_gameLogger->logAndDraw(
                Helper::getColorString(p_playerTwo->getColorCode()) + p_playerTwo->getName() + " won the game!");
    } else {
        p_gameLogger->logAndDraw(
                Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName() + " won the game!");
    }

    std::cout << std::endl << Helper::getColorString(GREEN) << "Press enter to leave :)";
    getchar();
}

void GameManager::nextRound() {
    p_gameLogger->log(
            Helper::getColorString(BLUE) + Helper::getColorString(BOLD) + "Round " + std::to_string(m_currentRound) +
            ":");

    //1.Give currency to both players
    p_playerOne->addCurrency(m_currencyAddedPerRound);
    p_playerTwo->addCurrency(m_currencyAddedPerRound);
    p_gameLogger->log("Both players received "
                      + Helper::getColorString(YELLOW) + std::to_string(m_currencyAddedPerRound) + " coins.");

    //2. Player One turn
    p_gameLogger->log(Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName()
                      + Helper::getColorString(RESET) + " turn:");
    playTurn(p_playerOne);
    p_gameLogger->draw();

    //3. Player Two turn
    p_gameLogger->logAndDraw(Helper::getColorString(p_playerTwo->getColorCode()) + p_playerTwo->getName()
                             + Helper::getColorString(RESET) + " turn:");
    playTurn(p_playerTwo);
    p_gameLogger->draw();

    //4.Save state
    saveState();
}

void GameManager::playTurn(const std::shared_ptr<IPlayer> &pPlayer) {
    //Make actions 1
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 1 Phase");
    p_board->doActions(1, pPlayer);
    Helper::Sleep(m_sleepBetweenActions);
    if (p_board->isOneBaseDestroyed()) return; // Skip other actions if one base has been destroyed

    //Make actions 2
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 2 Phase");
    p_board->doActions(2, pPlayer);
    Helper::Sleep(m_sleepBetweenActions);
    if (p_board->isOneBaseDestroyed()) return;

    //Make actions 3
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 3 Phase");
    p_board->doActions(3, pPlayer);
    Helper::Sleep(m_sleepBetweenActions);
    if (p_board->isOneBaseDestroyed()) return;

    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Buying Phase");
    if (p_board->canPlayerAddUnit(*pPlayer)) {
        if (p_buyingManager->getMinimalPrice() <= pPlayer->getCurrency()) {
            // Call specialized version that will return a unit choice
            // TODO following presentation: add possibility to skip buying phase
            int choice = pPlayer->chooseUnitToBuy(p_buyingManager->getPurchasableUnits());
            auto unitToBuy = p_buyingManager->createUnit(choice);
            // createUnit returns unit with empty owner player so we have to set it explicitly
            unitToBuy->setOwner(pPlayer);
            p_board->addUnit(unitToBuy, pPlayer);
        }
            // Player has not enough coins to buy even buy the cheapest unit
        else {
            p_gameLogger->log(Helper::getColorString(pPlayer->getColorCode()) + pPlayer->getName()
                              + Helper::getColorString(RESET) + " has not enough " + Helper::getColorString(YELLOW) +
                              "coins" + Helper::getColorString(RESET) + " to buy any unit. Skipping buying phase...");
        }
    }
        // Player's base is occupied and we can't spawn new unit
    else {
        p_gameLogger->log(Helper::getColorString(pPlayer->getColorCode()) + pPlayer->getName()
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