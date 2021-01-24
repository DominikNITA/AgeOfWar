//
// Created by Dominik on 12/28/2020.
//

#include "GameLogger.hpp"
#include "../utility/Helper.hpp"

void GameLogger::log(const std::string &message) {
    if(_messages.size() >= _maxBufferSize){
        _messages.erase(_messages.begin());
    }
    _messages.push_back(message);
}

void GameLogger::logAndDraw(const std::string &message) {
    log(message);
    draw();
}

void GameLogger::draw() {
    //Remove old logs
    clear();

    //Print new logs
    for (int i = 0; i < _messages.size(); ++i) {
        Helper::setColor(RESET);
        std::cout << i << ":" << _messages[i] << std::endl;
        Helper::setColor(RESET);
    }

    //Update the last size of buffer
    _lastDisplayedMessagesCount = _messages.size();
}

GameLogger::~GameLogger() {
    _messages.clear();
}

void GameLogger::clear() {
    for (int i = 0; i < _lastDisplayedMessagesCount; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
    _lastDisplayedMessagesCount = 0;
}


