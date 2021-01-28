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
    /// Constructor for new game
    /// \param mode Choosen mode (1 for PlayerVsAI and 2 for PlayerVsPlayer)
    /// \param name Unique name of the game
    GameManager(int mode, std::string name);

    /// Default constructor used for serialization
    GameManager() {
        // We consider that all games use the same units and prices
        initializeBuyingManager();
    };

    /// Default destructor
    ~GameManager() = default;

    /// Launch the game with current settings
    void startGame();

private:
    //Variables
    int m_roundLimit = 100;
    int m_currentRound = 0;
    int m_sleepBetweenActions = 750;
    int m_boardSize = 12;
    int m_mode;
    int m_currencyAddedPerRound = 8;
    std::string m_name;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;
    std::unique_ptr<Board> p_board;
    std::unique_ptr<BuyingManager> p_buyingManager;

    //Methods
    /// Main game loop logic
    void gameLoop();

    /// Starts next round consisting of: adding currency for both players, first player's turn and second player's turn
    void nextRound();

    /// Perform actions and possibly buy unit for specified player
    /// \param pPlayer
    void playTurn(const std::shared_ptr<IPlayer> &pPlayer);

    /// Update console view. For now same as Board::updateView(), but might change in the future
    void redrawAll();

    /// Create and initialize BuyingManager with purchasable units
    void initializeBuyingManager();

    /// Save game state to the file
    void saveState();

    // SERIALIZATION ZONE
    // cereal becomes friend class so it can modify member fields on deserialization
    friend class cereal::access;

    template<class Archive>
    void serialize(Archive &archive) {
        archive(CEREAL_NVP(m_roundLimit), CEREAL_NVP(m_currentRound), CEREAL_NVP(m_mode), CEREAL_NVP(m_name),
                CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo), CEREAL_NVP(p_board), CEREAL_NVP(p_gameLogger));
    }
};

#endif //AGEOFWAR_GAMEMANAGER_HPP