#include "GameLogger.hpp"
#include "../utility/Helper.hpp"

GameLogger::~GameLogger() {
    m_messages.clear();
}

void GameLogger::log(const std::string &message) {
    // If we achieved max capacity we have to delete the oldest messages (it's positioned at the beginning of the vector)
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

    //Print new logs
    for (auto & m_message : m_messages) {
        Helper::setColor(RESET);
        //adding left margin for better visibility
        std::cout << " " << m_message << std::endl;
        Helper::setColor(RESET);
    }

    //Update the last count of displayed messages
    m_lastDisplayedMessagesCount = m_messages.size();
}

void GameLogger::clear() {
    for (int i = 0; i < m_lastDisplayedMessagesCount; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
    m_lastDisplayedMessagesCount = 0;
}