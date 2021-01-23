//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMEMANAGER_HPP
#define AGEOFWAR_GAMEMANAGER_HPP


#include "../players/IPlayer.hpp"
#include "Board.hpp"
#include "GameLogger.hpp"
#include "UnitFactory.hpp"
#include "../units/Archer.hpp"
#include "../units/Catapult.hpp"
#include "../units/Fantassin.hpp"
#include "BuyingManager.hpp"
#include <memory>
#include <cereal/types/memory.hpp>
#include <cereal/archives/xml.hpp>

class GameManager {
public:
    GameManager(int mode);
    GameManager(const std::string& fileName);
    GameManager() {}
    GameManager(int roundLimit,int roundCounter,std::shared_ptr<IPlayer> playerOne, std::shared_ptr<IPlayer> playerTwo, int mode) : _roundCounter(roundCounter),_roundLimit(roundLimit),_mode(mode)
        {
            p_playerOne = playerOne;
            p_playerTwo = playerTwo;
        }
    ~GameManager();
    void startGame();
    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(_roundLimit),CEREAL_NVP(_roundCounter),CEREAL_NVP(p_playerOne),CEREAL_NVP(p_playerTwo),CEREAL_NVP(_mode));
    }
    int getRoundLimit() {return p_playerOne->getColorCode();}

    //
private:
    //Variables
    int _roundLimit = 15;
    int _sleepBetweenActions = 750;
    int _boardSize = 12;
    int _mode;
    bool _isFinished = false;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    int _roundCounter;
    GameLogger* p_gameLogger;
    Board* p_board;
    BuyingManager* p_buyingManager;
    //Methods
    void gameLoop();
    void nextRound();
    void doActions(int actionNumber, std::shared_ptr<IPlayer> pPlayer);
    void doAction(IAction* pAction);
    void playTurn(std::shared_ptr<IPlayer> pPlayer);
    void redrawAll();


    bool isOneBaseDestroyed();
};

#endif //AGEOFWAR_GAMEMANAGER_HPP