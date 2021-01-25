//
// Created by dominik on 12/27/20.
//

#include "IPlayer.hpp"

IPlayer::IPlayer(int number, std::string name, std::shared_ptr<GameLogger> pGameLogger) {
    m_number = number;
    m_colorCode = number == 1 ? MAGENTA : CYAN;
    p_base.reset(new Base());
    p_gameLogger = pGameLogger;
    m_name = name;
}

