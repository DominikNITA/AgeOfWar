//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMEMANAGER_HPP
#define AGEOFWAR_GAMEMANAGER_HPP


#include "../players/IPlayer.hpp"
#include "Board.hpp"
#include "GameLogger.hpp"
#include "../units/IPurchasable.h"
#include "UnitFactory.hpp"
#include "../units/Archer.hpp"
#include "../units/Catapult.hpp"
#include "../units/Fantassin.hpp"
#include "BuyingManager.hpp"

#define Sleep std::this_thread::sleep_for(std::chrono::milliseconds(_sleepBetweenActions))

class GameManager {
public:
    GameManager(int mode);
    ~GameManager();
    void startGame();
    void buyUnit(IBaseUnit* unit);
private:
    //Variables
    int _roundLimit = 15;
    int _sleepBetweenActions = 500;
    int _mode;
    IPlayer* p_playerOne;
    IPlayer* p_playerTwo;
    int _roundCounter;
    GameLogger* p_gameLogger;
    Board* p_board;
    BuyingManager* p_buyingManager;
    //Methods
    void gameLoop();
    void nextRound();
    void doActions(int actionNumber, IPlayer* pPlayer);
    void doAction(IAction* pAction);
    void playTurn(IPlayer* pPlayer);
};

#endif //AGEOFWAR_GAMEMANAGER_HPP