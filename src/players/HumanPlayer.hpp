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

    HumanPlayer() = default;

    int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) override;

    template<class Archive> void serialize(Archive & archive) {
        archive(CEREAL_NVP(m_number), CEREAL_NVP(m_name), CEREAL_NVP(m_colorCode), CEREAL_NVP(m_currency),
                CEREAL_NVP(p_base), CEREAL_NVP(p_gameLogger));
    }

//    template <class Archive>
//    static void load_and_construct( Archive & ar, cereal::construct<HumanPlayer> & construct )
//    {
//        int number;
//        std::string name;
//        int colorCode;
//        int currency = 10;
//        std::shared_ptr<Base> pbase;
//        ar(number,name,colorCode,currency,pbase);
//        construct( number,name,colorCode,currency,pbase);
//    }
};
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
CEREAL_REGISTER_TYPE(HumanPlayer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(IPlayer, HumanPlayer)

#endif //AGEOFWAR_HUMANPLAYER_HPP
