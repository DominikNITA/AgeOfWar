//
// Created by Dominik on 12/28/2020.
//

#include "GameLogger.hpp"
#include "../utility/Helper.hpp"

void GameLogger::log(const std::string &message) {
    if(m_messages.size() >= m_maxBufferSize){
        m_messages.erase(m_messages.begin());
    }
    m_messages.push_back(message);
}

void GameLogger::logAndDraw(const std::string &message) {
    log(message);
    draw();
}

void GameLogger::draw() {
    //Remove old logs
    clear();

    //std::cout << "Game logs: " << std::endl;
    //Print new logs
    for (auto & m_message : m_messages) {
        Helper::setColor(RESET);
        //adding one space for left margin
        std::cout << " " << m_message << std::endl;
        Helper::setColor(RESET);
    }

    //Update the last size of buffer
    m_lastDisplayedMessagesCount = m_messages.size();
}

GameLogger::~GameLogger() {
    m_messages.clear();
}

void GameLogger::clear() {
    for (int i = 0; i < m_lastDisplayedMessagesCount; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
    m_lastDisplayedMessagesCount = 0;
}


