//
// Created by Dominik on 12/28/2020.
//

#include "GameLogger.hpp"
#include "../utility/ConsoleHelper.hpp"

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
//    ConsoleHelper::clearScreen();
//    ConsoleHelper::moveToScreenStart();

//    //Remove old logs
    for (int i = 0; i < _lastBufferSize; ++i) {
        ConsoleHelper::moveCursorUp();
        ConsoleHelper::eraseLine();
    }
//    ConsoleHelper::moveToLineStart();
    //Print new logs
    for (auto & i : _buffer) {
        ConsoleHelper::setColor(RESET);
        std::cout << i << std::endl;
        ConsoleHelper::setColor(RESET);
    }
    //Update the last size of buffer
    _lastBufferSize = _buffer.size();
}

GameLogger::~GameLogger() {
    _buffer.clear();
}


