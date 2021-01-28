//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_GAMELOGGER_HPP
#define AGEOFWAR_GAMELOGGER_HPP


#include <vector>
#include <string>

#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>

class GameLogger{
public:
    /// Default constructor
    GameLogger() = default;

    /// Destructor clearing messages
    ~GameLogger();

    /// Add message to the buffor and delete oldest message when needed
    void log(const std::string& message);

    /// Add message and draw it
    void logAndDraw(const std::string& message);

    /// Clear console view output
    void clear();

    /// Update messages view in the console
    void draw();

private:
    int m_maxBufferSize = 20;
    int m_lastDisplayedMessagesCount = 0;
    std::vector<std::string> m_messages;

    // Serialization
    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_maxBufferSize), CEREAL_NVP(m_messages));
    }
};


#endif //AGEOFWAR_GAMELOGGER_HPP
