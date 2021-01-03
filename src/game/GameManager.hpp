//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMEMANAGER_HPP
#define AGEOFWAR_GAMEMANAGER_HPP


#include "../players/IPlayer.hpp"
#include "Board.hpp"
#include "CombatLogger.hpp"
#include "../units/IPurchasable.h"

class GameManager {
public:
    GameManager(int mode);
    ~GameManager();
    void StartGame();
private:
    //Variables
    int _mode;
    IPlayer* p_playerOne;
    IPlayer* p_playerTwo;
    int _roundCounter;
    CombatLogger _combatLogger;
    Board* p_board;
    //Methods
    void GameLoop();
    void NextRound();
    void DoActions(int actionNumber, IPlayer* pPlayer);
    void DoAction(IAction* pAction);
    void PlayTurn(IPlayer* pPlayer);
    void BuyUnit(IPlayer* pBuyer,const IPurchasable& purchasableUnit);
};

#endif //AGEOFWAR_GAMEMANAGER_HPP