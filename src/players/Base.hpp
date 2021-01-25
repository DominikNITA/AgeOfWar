//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BASE_HPP
#define AGEOFWAR_BASE_HPP


#include "../units/IAttackable.hpp"
#include "../utility/IDrawable.hpp"

#include <cereal/archives/xml.hpp>

class Base : public IAttackable , public IDrawable{
public:
    Base();
    Base(int hp) {
        m_hp = hp;
    };
    virtual ~Base() = default;
    virtual void draw();


    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(m_hp));
    }
};


#endif //AGEOFWAR_BASE_HPP
