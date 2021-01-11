//
// Created by Dominik on 1/3/2021.
//

#ifndef AGEOFWAR_UNITFACTORY_HPP
#define AGEOFWAR_UNITFACTORY_HPP


#include "../units/IBaseUnit.hpp"
#include "../units/IPurchasable.h"

//https://stackoverflow.com/questions/1883862/c-oop-list-of-classes-class-types-and-creating-instances-of-them

template <typename T> struct IUnitFactory { virtual IPurchasable<T>* create(IPlayer* pOwner) = 0;};

template <typename Type> struct UnitFactory : public IUnitFactory<Type> {
    virtual Type* create(IPlayer* pOwner){
        return new Type(pOwner);
    }
};


#endif //AGEOFWAR_UNITFACTORY_HPP
