#ifndef AGEOFWAR_BASE_HPP
#define AGEOFWAR_BASE_HPP

#include <cereal/archives/xml.hpp>
#include "../units/IAttackable.hpp"



class Base : public IAttackable{
public:
    Base(){
        m_hp = 100;
    }
    Base(int hp) {
        m_hp = hp;
    };
    virtual ~Base() = default;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_hp));
    }
};


#endif //AGEOFWAR_BASE_HPP
