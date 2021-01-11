//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMEMANAGER_HPP
#define AGEOFWAR_GAMEMANAGER_HPP


#include "../players/IPlayer.hpp"
#include "Board.hpp"
#include "CombatLogger.hpp"
#include "../units/IPurchasable.h"
#include "UnitFactory.hpp"
#include "../units/Archer.hpp"
#include "../units/Catapult.hpp"
#include "../units/Fantassin.hpp"

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
//    IUnitFactory<IBaseUnit>* unitFactories[3] = {
//            new UnitFactory<Archer>,
//            new UnitFactory<Catapult>,
//            new UnitFactory<Fantassin>,
//    };
    //Methods
    void GameLoop();
    void NextRound();
    void DoActions(int actionNumber, IPlayer* pPlayer);
    void DoAction(IAction* pAction);
    void PlayTurn(IPlayer* pPlayer);
};

#endif //AGEOFWAR_GAMEMANAGER_HPP