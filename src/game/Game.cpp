//
// Created by Dominik on 12/28/2020.
//

#include <iostream>
#include "Game.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"
#include "../units/Archer.hpp"

Game::Game(int mode) : _mode(mode) {
    _roundCounter = 0;
    _playerOne = new HumanPlayer(1);
    if(mode == 0){
        _playerTwo = new HumanPlayer(2);
    }
    else{
        _playerTwo = new ComputerPlayer(2);
    }
    _board = Board();

    _combatLogger = CombatLogger();
}

void Game::StartGame() {
    GameLoop();
}

void Game::NextRound() {
    //1.Give currency to both players
    _playerOne->AddCurrency(8);
    _playerTwo->AddCurrency(8);
    //2. Player One turn
    PlayTurn(_playerOne);
    //3. Player Two turn
    PlayTurn(_playerTwo);
}

void Game::PlayTurn(IPlayer* player) {
    //Make Action 1
    DoActions(1,player);
    //Make Action 2
    DoActions(2,player);
    //Make Action 3
    DoActions(3,player);
    //TODO: Buy unit logic
    _board.AddUnit(new Archer(player),player);
}

void Game::GameLoop() {
    while(_roundCounter < 2){
        std::cout << "Current round " << _roundCounter << std::endl;
        NextRound();
        _roundCounter++;
    }
}

void Game::DoActions(int actionNumber, IPlayer* player) {
    auto units = _board.getPlayerUnits(player, actionNumber == 1);
    std::cout<< "Unit count for player " << player->GetNumber() << " =>"  << units.size()<<std::endl;
}

