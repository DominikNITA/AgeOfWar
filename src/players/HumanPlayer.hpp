//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_HUMANPLAYER_HPP
#define AGEOFWAR_HUMANPLAYER_HPP


#include "IPlayer.hpp"
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

class HumanPlayer : public IPlayer{

public:
    HumanPlayer(int number, std::string name, std::shared_ptr<GameLogger> pGameLogger);
    HumanPlayer(int number, std::string name,int colorCode, int currency, std::shared_ptr<Base> base);

    int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) override;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(_number),CEREAL_NVP(_name),CEREAL_NVP(_colorCode),CEREAL_NVP(_currency),CEREAL_NVP(p_base));
    }

    template <class Archive>
    static void load_and_construct( Archive & ar, cereal::construct<HumanPlayer> & construct )
    {
        int number;
        std::string name;
        int colorCode;
        int currency = 10;
        std::shared_ptr<Base> pbase;
        ar(number,name,colorCode,currency,pbase);
        construct( number,name,colorCode,currency,pbase);
    }
};
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
CEREAL_REGISTER_TYPE(HumanPlayer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(IPlayer, HumanPlayer)

#endif //AGEOFWAR_HUMANPLAYER_HPP
