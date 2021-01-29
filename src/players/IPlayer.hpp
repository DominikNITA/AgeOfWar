#ifndef AGEOFWAR_IPLAYER_HPP
#define AGEOFWAR_IPLAYER_HPP


#include <vector>
#include "Base.hpp"
#include "../game/GameLogger.hpp"
#include "../utility/Helper.hpp"

class IPlayer {
public:
    IPlayer(int number, std::string name, std::shared_ptr<GameLogger> pGameLogger);
    IPlayer() = default;

    virtual ~IPlayer() {

    }

    //Getters
    int getCurrency() const { return m_currency; }
    std::shared_ptr<Base> getBase() { return p_base; }
    int getNumber() const {return  m_number;}
    int getColorCode() const {return m_colorCode; }
    std::string getName() const {return m_name; }
    //Methods
    void addCurrency(int amount) { m_currency += amount;}
    virtual int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) = 0;

protected:
    int m_number;
    std::string m_name;
    int m_colorCode;
    int m_currency = 10;
    std::shared_ptr<GameLogger> p_gameLogger;
    std::shared_ptr<Base> p_base;


//    template<class Archive> void serialize(Archive & archive){
//        archive(m_name);
//    }
};
#endif //AGEOFWAR_IPLAYER_HPP