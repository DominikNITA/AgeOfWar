//
// Created by Dominik on 12/28/2020.
//

#include "GameLogger.hpp"
#include "../utility/Helper.hpp"

void GameLogger::log(const std::string &message) {
    if(_buffer.size() >= _maxBufferSize){
        _buffer.erase(_buffer.begin());
    }
    _buffer.push_back(message);
}

void GameLogger::logAndDraw(const std::string &message) {
    log(message);
    draw();
}

void GameLogger::draw() {
    //Remove old logs
    clear();

    //Print new logs
    for (int i = 0; i < _buffer.size(); ++i) {
        Helper::setColor(RESET);
        std::cout << i << ":" << _buffer[i] << std::endl;
        Helper::setColor(RESET);
    }

    //Update the last size of buffer
    _lastBufferSize = _buffer.size();
}

GameLogger::~GameLogger() {
    _buffer.clear();
}

void GameLogger::clear() {
    for (int i = 0; i < _lastBufferSize; ++i) {
        Helper::moveCursorUp();
        Helper::eraseLine();
    }
    _lastBufferSize = 0;
}


