//
// Created by Dominik on 12/28/2020.
//

#include "Game.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/ComputerPlayer.hpp"

Game::Game(int mode) : _mode(mode) {
    _roundCounter = 0;
    _playerOne = new HumanPlayer();
    if(mode == 0){
        _playerTwo = new HumanPlayer();
    }
    else{
        _playerTwo = new ComputerPlayer();
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
    //Buy unit logic
}

void Game::GameLoop() {
    while(_roundCounter < 100){
        NextRound();
        _roundCounter++;
    }
}

void Game::DoActions(int actionNumber, IPlayer* player) {

}

