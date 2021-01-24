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
        initializeBuyingManager();
    };
//    GameManager(int roundLimit,int roundCounter, int mode,std::shared_ptr<IPlayer> playerOne, std::shared_ptr<IPlayer> playerTwo, std::unique_ptr<Board> pboard) : _currentRound(roundCounter),_roundLimit(roundLimit),_mode(mode)
//        {
//            p_playerOne = playerOne;
//            p_playerTwo = playerTwo;
//            std::cout << pboard->test() << std::endl;
//        }
    ~GameManager();

    void startGame();

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(_roundLimit), CEREAL_NVP(_currentRound), CEREAL_NVP(_mode), CEREAL_NVP(_name), CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo), CEREAL_NVP(p_board), CEREAL_NVP(p_gameLogger));
    }
private:
    //Variables
    int _roundLimit = 15;
    int _currentRound = 0;
    int _sleepBetweenActions = 750;
    int _boardSize = 12;
    int _mode = -1;
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
    void initializeBuyingManager();
    bool isOneBaseDestroyed();
    void saveState();
};

#endif //AGEOFWAR_GAMEMANAGER_HPP