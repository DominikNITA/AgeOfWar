//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include <thread>
#include "GameManager.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"
#include "../units/Archer.hpp"
#include "actions/ActionAttack.hpp"
#include "actions/ActionNone.hpp"
#include "actions/ActionMove.hpp"
#include "../utility/ConsoleHelper.hpp"

GameManager::GameManager(int mode) : _mode(mode) {
    _roundCounter = 0;

    p_gameLogger = new GameLogger();

    p_playerOne = new HumanPlayer(1,p_gameLogger);
    if(_mode == 0){
        p_playerTwo = new HumanPlayer(2,p_gameLogger);
    }
    else{
        p_playerTwo = new ComputerPlayer(2,p_gameLogger);
    }

    p_board = new Board(p_playerOne, p_playerTwo, p_gameLogger,_boardSize);

    p_buyingManager = new BuyingManager();
    p_buyingManager->addUnit("fantassin",10,new UnitFactory<Fantassin>);
    p_buyingManager->addUnit("archer",12,new UnitFactory<Archer>);
    p_buyingManager->addUnit("catapult",20,new UnitFactory<Catapult>);
}

GameManager::~GameManager() {
    if(p_playerOne != nullptr){
        delete p_playerOne;
        p_playerOne = nullptr;
    }
    if(p_playerTwo != nullptr){
        delete p_playerTwo;
        p_playerTwo = nullptr;
    }
    if(p_board != nullptr){
        delete p_board;
        p_board = nullptr;
    }
    delete p_buyingManager;
}

void GameManager::startGame() {
    p_board->draw();
    gameLoop();
}

void GameManager::nextRound() {
    p_gameLogger->log(ConsoleHelper::getColorString(BLUE) + ConsoleHelper::getColorString(BOLD) +"Round " + std::to_string(_roundCounter) + ":");

    //1.Give currency to both players
    p_playerOne->addCurrency(8);
    p_playerTwo->addCurrency(8);
    p_gameLogger->log("Both players received "
    + ConsoleHelper::getColorString(YELLOW) + std::to_string(8) + " coins.");

    //2. Player One turn
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(p_playerOne->getColorCode()) + "Player one turn:");
    playTurn(p_playerOne);
    p_gameLogger->draw();

    //3. Player Two turn
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(p_playerTwo->getColorCode()) + "Player two turn:");
    p_gameLogger->draw();
    playTurn(p_playerTwo);
}

void GameManager::playTurn(IPlayer* pPlayer) {
    //Make Action 1
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(GREEN)+"Action 1 Phase");
    doActions(1, pPlayer);

    //Make Action 2
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(GREEN)+"Action 2 Phase");
    doActions(2, pPlayer);

    //Make Action 3
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(GREEN)+"Action 3 Phase");
    doActions(3, pPlayer);
    p_gameLogger->draw();

    if(p_board->canPlayerAddUnit(pPlayer)){
        if(p_buyingManager->getMinimalPrice() <= pPlayer->GetCurrency()){

            int choice = pPlayer->chooseUnitToBuy(p_buyingManager->getPurchasableUnits());
            IBaseUnit* unitToBuy = p_buyingManager->returnUnit(choice);
            unitToBuy->setOwner(pPlayer);
            p_board->addUnit(unitToBuy, pPlayer);
        }
        else{
            p_gameLogger->logAndDraw("Not enough coins to buy unit for player " + std::to_string(pPlayer->GetNumber()));
        }
    }
    else{
        p_gameLogger->logAndDraw("Base position is occupied for player " + std::to_string(pPlayer->GetNumber()));
    }
    redrawAll();
}

void GameManager::gameLoop() {
    while(_roundCounter < _roundLimit){
        _roundCounter++;
        nextRound();
    }
}

void GameManager::doActions(int actionNumber, IPlayer* pPlayer) {
    auto units = p_board->getPlayerUnits(pPlayer, actionNumber == 1);

    if(units.empty()){
        p_gameLogger->logAndDraw("Player has no units!");
    }

    for (int i = 0; i < units.size(); ++i) {
        //Catapult could kill it's own unit before it's turn -> Segmentation fault
        if(units[i] == nullptr) continue;

        auto action = units[i]->getAction(actionNumber, p_board->getDistancesToEnemies(units[i]));
        doAction(action);
        Sleep;
        redrawAll();
    }
    Sleep;
}

void GameManager::doAction(IAction *pAction) {
    if(pAction == nullptr){
        std::cout << "Null action pointer\n";
        return;
    }
    if(auto pMoveAction = dynamic_cast<ActionMove*>(pAction)){
        p_board->moveUnitForward(pMoveAction->getUnit(), pMoveAction->getCount());
    }
    else if(auto pAttackAction = dynamic_cast<ActionAttack*>(pAction)){
        p_board->attackRelativePositions(dynamic_cast<IBaseUnit*>(pAttackAction->GetAttacker()), pAttackAction->GetAttackedPositions());
    }
    else if (auto pNoneAction = dynamic_cast<ActionNone*>(pAction)) {
        /*std::cout << "Nothing todo!\n";*/
    }
    else{
        std::cout << "ERROR: unknown action type: " << pAction->GetActionLog() << std::endl;
    }
}

void GameManager::redrawAll() {
    p_gameLogger->clear();
    p_board->clear();
    p_board->draw();
    p_gameLogger->draw();
}




