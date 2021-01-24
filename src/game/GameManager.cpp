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

GameManager::GameManager(int mode, std::string name) : _mode(mode), _name(name) {
    _currentRound = 0;
    p_gameLogger.reset(new GameLogger());

    std::string playerName;

    std::cout << "First player nick: ";
    std::cin >> playerName;
    Helper::erasePreviousLine();
    p_playerOne.reset(new HumanPlayer(1,playerName,p_gameLogger));
    if(_mode == 2){
        std::cout << "Second player nick: ";
        std::cin >> playerName;
        Helper::erasePreviousLine();
        p_playerTwo.reset(new HumanPlayer(2,playerName,p_gameLogger));
    }
    else{
        p_playerTwo.reset(new ComputerPlayer(2,p_gameLogger));
    }

    p_board.reset(new Board(p_playerOne, p_playerTwo, p_gameLogger,_boardSize));

    initializeBuyingManager();
}

void GameManager::initializeBuyingManager() {
    p_buyingManager.reset(new BuyingManager());
    p_buyingManager->addUnit("fantassin",10,new UnitFactory<Fantassin>);
    p_buyingManager->addUnit("archer",12,new UnitFactory<Archer>);
    p_buyingManager->addUnit("catapult",20,new UnitFactory<Catapult>);
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
    std::cout<< "Age of War - 2020/21 - Polytech Paris-Saclay - Youssef MCHAREK, Dominik NITA" << std::endl << std::endl;

    p_board->draw();

    gameLoop();
}

void GameManager::gameLoop() {
    //TOCHECK priority of oeprators
    while((_currentRound < _roundLimit) && !_isFinished){
        _currentRound++;
        nextRound();
    }
    p_gameLogger->logAndDraw(Helper::getColorString(YELLOW) + "Game has finished!");
    if(_currentRound == _roundLimit){
        p_gameLogger->logAndDraw(Helper::getColorString(BLUE) + "It's a draw: maximum amount of rounds passed!");
        return;
    }
    if(p_playerOne->getBase()->GetHp() <= 0){
        p_gameLogger->logAndDraw( Helper::getColorString(p_playerTwo->getColorCode()) + p_playerTwo->getName() + " won the game!");
        return;
    }
    else{
        p_gameLogger->logAndDraw( Helper::getColorString(p_playerOne->getColorCode()) + p_playerOne->getName() + " won the game!");
        return;
    }
}

void GameManager::nextRound() {
    p_gameLogger->log(Helper::getColorString(BLUE) + Helper::getColorString(BOLD) + "Round " + std::to_string(_currentRound) + ":");

    //1.Give currency to both players
    p_playerOne->addCurrency(8);
    p_playerTwo->addCurrency(8);
    p_gameLogger->log("Both players received "
                      + Helper::getColorString(YELLOW) + std::to_string(8) + " coins.");

    //2. Player One turn
    p_gameLogger->logAndDraw(Helper::getColorString(p_playerOne->getColorCode()) + "Player one turn:");
    playTurn(p_playerOne);
    p_gameLogger->draw();

    //3. Player Two turn
    p_gameLogger->logAndDraw(Helper::getColorString(p_playerTwo->getColorCode()) + "Player two turn:");
    p_gameLogger->draw();
    playTurn(p_playerTwo);

    //4.Sauvgarder l'etat
    saveState();
}

void GameManager::playTurn(std::shared_ptr<IPlayer> pPlayer) {

    //Make Action 1
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 1 Phase");
    doActions(1, pPlayer);
    if(_isFinished) return;

    //Make Action 2
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 2 Phase");
    doActions(2, pPlayer);
    if(_isFinished) return;

    //Make Action 3
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Action 3 Phase");
    doActions(3, pPlayer);
    p_gameLogger->draw();

    if(_isFinished) return;
    p_gameLogger->logAndDraw(Helper::getColorString(GREEN) + "Buying Phase");
    if(p_board->canPlayerAddUnit(pPlayer)){
        if(p_buyingManager->getMinimalPrice() <= pPlayer->getCurrency()){

            int choice = pPlayer->chooseUnitToBuy(p_buyingManager->getPurchasableUnits());
            auto unitToBuy = p_buyingManager->returnUnit(choice);
            unitToBuy->setOwner(pPlayer);
            p_board->addUnit(unitToBuy, pPlayer);
        }
        else{
            p_gameLogger->logAndDraw("Not enough coins to buy unit for player " + std::to_string(pPlayer->getNumber()));
        }
    }
    else{
        p_gameLogger->logAndDraw("Base position is occupied for player " + std::to_string(pPlayer->getNumber()));
    }
    redrawAll();
    Helper::Sleep(1500);
}



void GameManager::doActions(int actionNumber, std::shared_ptr<IPlayer> pPlayer) {
    if(actionNumber == 3) p_gameLogger->logAndDraw("a");
    auto units = p_board->getPlayerUnits(pPlayer, actionNumber == 1);
    if(actionNumber == 3) p_gameLogger->logAndDraw("b");
    if(units.empty()){
        p_gameLogger->logAndDraw("Player has no units!");
    }
    if(actionNumber == 3) p_gameLogger->logAndDraw("c");
    for (int i = 0; i < units.size(); ++i) {
        //Catapult could kill it's own unit before it's turn -> Segmentation fault
//        if(units[i] == nullptr) continue;
        if(actionNumber == 3) p_gameLogger->logAndDraw("c1");
        if(actionNumber == 3) p_gameLogger->logAndDraw(units[i]->GetHp() + "");
        auto action = units[i]->getAction(actionNumber, p_board->getDistancesToEnemies(units[i]));
        if(actionNumber == 3) p_gameLogger->logAndDraw("c2");
        doAction(action);
        if(actionNumber == 3) p_gameLogger->logAndDraw("c3");
        if(isOneBaseDestroyed()){
            _isFinished = true;
        }
        Helper::Sleep(150);
        redrawAll();
        if(actionNumber == 3) p_gameLogger->logAndDraw("c4");
    }
    if(actionNumber == 3) p_gameLogger->logAndDraw("d");
    Helper::Sleep(_sleepBetweenActions);
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
        p_board->attackRelativePositions(std::dynamic_pointer_cast<IBaseUnit>(pAttackAction->GetAttacker()), pAttackAction->GetAttackedPositions());
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

bool GameManager::isOneBaseDestroyed() {
    return p_playerOne->getBase()->GetHp() <= 0 || p_playerTwo->getBase()->GetHp() <= 0;
}

void GameManager::saveState() {
    std::ofstream os("saves/"+_name+".xml");
    cereal::XMLOutputArchive archive(os);
    archive(*this);
}

