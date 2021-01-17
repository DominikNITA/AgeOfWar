//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMELOGGER_HPP
#define AGEOFWAR_GAMELOGGER_HPP


#include <vector>
#include <string>
#include "../utility/IDrawable.hpp"

class GameLogger : public IDrawable {
public:
    void log(const std::string& message);
    void logAndDraw(const std::string& message);
    virtual ~GameLogger();

    void draw() override;

private:
    int _maxBufferSize = 12;
    int _lastBufferSize = 0;
    std::vector<std::string> _buffer;
};


#endif //AGEOFWAR_GAMELOGGER_HPP
