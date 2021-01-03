//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "GameManager.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"
#include "../units/Archer.hpp"
#include "actions/ActionAttack.hpp"
#include "actions/ActionNone.hpp"
#include "actions/ActionMove.hpp"

GameManager::GameManager(int mode) : _mode(mode) {
    _roundCounter = 0;
    p_playerOne = new HumanPlayer(1);
    if(mode == 0){
        p_playerTwo = new HumanPlayer(2);
    }
    else{
        p_playerTwo = new ComputerPlayer(2);
    }
    _board = Board();

    _combatLogger = CombatLogger();
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
}

void GameManager::StartGame() {
    GameLoop();
}

void GameManager::NextRound() {
    //1.Give currency to both players
    p_playerOne->addCurrency(8);
    p_playerTwo->addCurrency(8);
    //2. Player One turn
    PlayTurn(p_playerOne);
    //3. Player Two turn
    PlayTurn(p_playerTwo);
}

void GameManager::PlayTurn(IPlayer* player) {
    //Make Action 1
    DoActions(1,player);
    //Make Action 2
    DoActions(2,player);
    //Make Action 3
    DoActions(3,player);
    //TODO: Buy unit logic
    _board.addUnit(new Archer(player), player);
}

void GameManager::GameLoop() {
    while(_roundCounter < 10){
        std::cout << "Current round " << _roundCounter << std::endl;
        NextRound();
        _roundCounter++;
    }
}

void GameManager::DoActions(int actionNumber, IPlayer* player) {
    auto units = _board.getPlayerUnits(player, actionNumber == 1);

    for (int i = 0; i < units.size(); ++i) {
        auto action = units[i]->GetAction(actionNumber, _board.getDistancesToEnemies(units[i]));
        DoAction(action);
    }
    std::cout<< "Unit count for player " << player->GetNumber() << " =>"  << units.size()<<std::endl;
}

void GameManager::DoAction(IAction *pAction) {
    if(pAction == nullptr){
        std::cout << "Null action pointer\n";
        return;
    }
    if(auto pMoveAction = dynamic_cast<ActionMove*>(pAction)){
        _board.moveUnitForward(pMoveAction->getUnit(), pMoveAction->getCount());
    }
    else if(auto pAttackAction = dynamic_cast<ActionAttack*>(pAction)){
        _board.attackRelativePositions(dynamic_cast<IBaseUnit*>(pAttackAction->GetAttacker()),pAttackAction->GetAttackedPositions());
    }
    else if (auto pNoneAction = dynamic_cast<ActionNone*>(pAction)) {
        /*std::cout << "Nothing todo!\n";*/
    }
    else{
        std::cout << "ERROR: unknown action type: " << pAction->GetActionLog() << std::endl;
    }
}

void GameManager::BuyUnit(IPlayer *buyer, const IPurchasable &purchasableUnit) {

}




