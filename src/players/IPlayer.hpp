//
// Created by dominik on 12/27/20.
//

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
    int getCurrency() const { return _currency; }
    std::shared_ptr<Base> getBase() { return p_base; }
    int getNumber() const {return  _number;}
    int getColorCode() const {return _colorCode; }
    std::string getName() const {return _name; }
    //Methods
    void addCurrency(int amount) { _currency += amount;}
    virtual int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) = 0;

protected:
    int _number;
    std::string _name;
    int _colorCode;
    int _currency = 10;
    std::shared_ptr<GameLogger> p_gameLogger;
    std::shared_ptr<Base> p_base;


//    template<class Archive> void serialize(Archive & archive){
//        archive(_name);
//    }
};
#endif //AGEOFWAR_IPLAYER_HPP