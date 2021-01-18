//
// Created by dominik on 12/27/20.
//

#include "IPlayer.hpp"

IPlayer::IPlayer(int number, GameLogger* pGameLogger) {
    _number = number;
    p_base = new Base();
    p_gameLogger = pGameLogger;
}

