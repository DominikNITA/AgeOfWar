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
//    GameManager(int roundLimit,int roundCounter, int mode,std::shared_ptr<IPlayer> playerOne, std::shared_ptr<IPlayer> playerTwo, std::unique_ptr<Board> pboard) : m_currentRound(roundCounter),m_roundLimit(roundLimit),m_mode(mode)
//        {
//            p_playerOne = playerOne;
//            p_playerTwo = playerTwo;
//            std::cout << pboard->test() << std::endl;
//        }
    ~GameManager() = default;

    void startGame();

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_roundLimit), CEREAL_NVP(m_currentRound), CEREAL_NVP(m_mode), CEREAL_NVP(m_name), CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo), CEREAL_NVP(p_board), CEREAL_NVP(p_gameLogger));
    }
private:
    //Variables
    int m_roundLimit = 15;
    int m_currentRound = 0;
    int m_sleepBetweenActions = 750;
    int m_boardSize = 12;
    int m_mode = -1;
    std::string m_name;
    bool m_isFinished = false;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;
    std::unique_ptr<Board> p_board;
    std::unique_ptr<BuyingManager> p_buyingManager;

    //Methods
    void gameLoop();
    void nextRound();
    void playTurn(std::shared_ptr<IPlayer> pPlayer);
    void redrawAll();
    void initializeBuyingManager();

    void saveState();
};

#endif //AGEOFWAR_GAMEMANAGER_HPP