//
// Created by Dominik on 1/3/2021.
//

#ifndef AGEOFWAR_UNITFACTORY_HPP
#define AGEOFWAR_UNITFACTORY_HPP


#include "../units/IBaseUnit.hpp"

//https://stackoverflow.com/questions/1883862/c-oop-list-of-classes-class-types-and-creating-instances-of-them

struct IUnitFactory { virtual std::shared_ptr<IBaseUnit> create(std::shared_ptr<IPlayer> pOwner) = 0;};

template <typename Type> struct UnitFactory : public IUnitFactory {
    virtual std::shared_ptr<IBaseUnit> create(std::shared_ptr<IPlayer> pOwner){
        return std::shared_ptr<IBaseUnit>(new Type(pOwner));
    }
};


#endif //AGEOFWAR_UNITFACTORY_HPP
