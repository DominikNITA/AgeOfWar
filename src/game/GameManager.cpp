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
    p_playerOne = new HumanPlayer(1);
    if(_mode == 0){
        p_playerTwo = new HumanPlayer(2);
    }
    else{
        p_playerTwo = new ComputerPlayer(2);
    }
    p_board = new Board(p_playerOne, p_playerTwo, 12);
    p_buyingManager = new BuyingManager();
    p_buyingManager->addUnit("fantassin",10,new UnitFactory<Fantassin>);
    p_buyingManager->addUnit("archer",12,new UnitFactory<Archer>);
    p_buyingManager->addUnit("catapult",20,new UnitFactory<Catapult>);
    p_gameLogger = new GameLogger();
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
    gameLoop();
}

void GameManager::nextRound() {
    p_gameLogger->log(ConsoleHelper::getColorString(BLUE) +"Round " + std::to_string(_roundCounter) + ":");

    //1.Give currency to both players
    p_playerOne->addCurrency(8);
    p_playerTwo->addCurrency(8);
    p_gameLogger->log("Both players received "
    + ConsoleHelper::getColorString(YELLOW) + std::to_string(8) + " coins.");

    //2. Player One turn
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(p_playerOne->getColorCode()) + "Player one turn:");
    playTurn(p_playerOne);

    //3. Player Two turn
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(p_playerTwo->getColorCode()) + "Player two turn:");
    playTurn(p_playerTwo);

    p_board->draw();
}

void GameManager::playTurn(IPlayer* pPlayer) {
    //Make Action 1
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(BLUE)+"Action 1 Phase");
    doActions(1, pPlayer);

    //Make Action 2
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(BLUE)+"Action 2 Phase");
    doActions(2, pPlayer);

    //Make Action 3
    p_gameLogger->logAndDraw(ConsoleHelper::getColorString(BLUE)+"Action 3 Phase");
    doActions(3, pPlayer);

    if(p_board->canPlayerAddUnit(pPlayer)){
        if(p_buyingManager->getMinimalPrice() <= pPlayer->GetCurrency()){
            int choice = pPlayer->chooseUnitToBuy(p_buyingManager->getPurchasableUnits());
            IBaseUnit* unitToBuy = p_buyingManager->returnUnit(choice);
            unitToBuy->setOwner(pPlayer);
            p_board->addUnit(unitToBuy, pPlayer);
        }
        else{
            std::cout << "Not enough coins to buy unit for player " << pPlayer->GetNumber() << std::endl;
        }
    }
    else{
        std::cout << "Base position is occupied for player " << pPlayer->GetNumber() << std::endl;
    }
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
        return;
    }

    for (int i = 0; i < units.size(); ++i) {
        auto action = units[i]->getAction(actionNumber, p_board->getDistancesToEnemies(units[i]));
        doAction(action);
        std::this_thread::sleep_for(std::chrono::milliseconds(_sleepBetweenActions));
    }
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

void GameManager::buyUnit(IBaseUnit * unit) {
    //TODO: implement

}




