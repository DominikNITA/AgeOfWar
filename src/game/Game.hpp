//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAME_HPP
#define AGEOFWAR_GAME_HPP


#include "../players/IPlayer.hpp"
#include "Board.hpp"
#include "CombatLogger.hpp"

class Game {
public:
    Game(int mode);
    void StartGame();
private:
    //Variables
    int _mode;
    IPlayer* _playerOne;
    IPlayer* _playerTwo;
    int _roundCounter;
    CombatLogger _combatLogger;
    Board _board;
    //Methods
    void GameLoop();
    void NextRound();
    void DoActions(int actionNumber, IPlayer* player);
    void PlayTurn(IPlayer* player);
    void BuyUnit(IPlayer* buyer,const IUnit& unit);
};


#endif //AGEOFWAR_GAME_HPP
