#ifndef AGEOFWAR_COMPUTERPLAYER_HPP
#define AGEOFWAR_COMPUTERPLAYER_HPP


#include "IPlayer.hpp"

class ComputerPlayer : public IPlayer {

public:
    ComputerPlayer(int number, std::shared_ptr<GameLogger> pGameLogger);
    ComputerPlayer(int number, std::string name,int colorCode, int currency, std::shared_ptr<Base> base);

    ComputerPlayer() = default;

    int chooseUnitToBuy(std::vector<std::pair<std::string, int>> unitsInfo) override;

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_number), CEREAL_NVP(m_name), CEREAL_NVP(m_colorCode), CEREAL_NVP(m_currency), CEREAL_NVP(p_base), CEREAL_NVP(p_gameLogger));
    }

//    template <class Archive>
//    static void load_and_construct( Archive & ar, cereal::construct<ComputerPlayer> & construct )
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
#include <cereal/types/memory.hpp>
CEREAL_REGISTER_TYPE(ComputerPlayer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(IPlayer, ComputerPlayer)

#endif //AGEOFWAR_COMPUTERPLAYER_HPP
