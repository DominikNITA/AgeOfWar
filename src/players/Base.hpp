//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BASE_HPP
#define AGEOFWAR_BASE_HPP


#include "../units/IAttackable.hpp"
#include "../utility/IDrawable.hpp"

class Base : public IAttackable , public IDrawable{
public:
    Base();
    virtual ~Base() = default;
    virtual void draw();
};


#endif //AGEOFWAR_BASE_HPP
