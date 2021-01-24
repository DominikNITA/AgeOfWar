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
    GameManager(int mode, std::string name);
    GameManager() {
        p_gameLogger = std::shared_ptr<GameLogger>(new GameLogger());
        p_buyingManager = std::unique_ptr<BuyingManager>(new BuyingManager());
        p_buyingManager->addUnit("fantassin",10,new UnitFactory<Fantassin>);
        p_buyingManager->addUnit("archer",12,new UnitFactory<Archer>);
        p_buyingManager->addUnit("catapult",20,new UnitFactory<Catapult>);
    };
    GameManager(int roundLimit,int roundCounter, int mode,std::shared_ptr<IPlayer> playerOne, std::shared_ptr<IPlayer> playerTwo, std::unique_ptr<Board> pboard) : _roundCounter(roundCounter),_roundLimit(roundLimit),_mode(mode)
        {
            p_playerOne = playerOne;
            p_playerTwo = playerTwo;
            std::cout << pboard->test() << std::endl;
        }
    ~GameManager();

    void startGame();

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(_roundLimit),CEREAL_NVP(_roundCounter),CEREAL_NVP(_mode),CEREAL_NVP(p_playerOne),CEREAL_NVP(p_playerTwo),CEREAL_NVP(p_board));
    }
    int getRoundLimit() {return p_playerOne->getColorCode();}

    //
private:
    //Variables
    int _roundLimit = 15;
    int _roundCounter;
    int _sleepBetweenActions = 750;
    int _boardSize = 12;
    int _mode;
    std::string _name;
    bool _isFinished = false;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;
    std::unique_ptr<Board> p_board;
    std::unique_ptr<BuyingManager> p_buyingManager;
    //Methods
    void gameLoop();
    void nextRound();
    void doActions(int actionNumber, std::shared_ptr<IPlayer> pPlayer);
    void doAction(IAction* pAction);
    void playTurn(std::shared_ptr<IPlayer> pPlayer);
    void redrawAll();


    bool isOneBaseDestroyed();

    void saveState();
};

#endif //AGEOFWAR_GAMEMANAGER_HPP