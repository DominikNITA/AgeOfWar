//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMELOGGER_HPP
#define AGEOFWAR_GAMELOGGER_HPP


#include <vector>
#include <string>
#include "../utility/IDrawable.hpp"
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>

class GameLogger : public IDrawable {
public:
    GameLogger() = default;
    void log(const std::string& message);
    void logAndDraw(const std::string& message);
    void clear();
    virtual ~GameLogger();

    void draw() override;

private:
    int m_maxBufferSize = 20;
    int m_lastDisplayedMessagesCount = 0;
    std::vector<std::string> m_messages;

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_maxBufferSize), CEREAL_NVP(m_messages));
    }
};


#endif //AGEOFWAR_GAMELOGGER_HPP
