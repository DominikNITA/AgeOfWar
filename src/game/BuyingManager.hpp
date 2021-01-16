//
// Created by Dominik on 1/16/2021.
//

#ifndef AGEOFWAR_BUYINGMANAGER_HPP
#define AGEOFWAR_BUYINGMANAGER_HPP

#include <vector>
#include "UnitFactory.hpp"


class BuyingManager {
public:
    BuyingManager() {}
    std::vector<std::pair<std::string,int>> getPurchasableUnits();
    void addUnit(std::string, int price, IUnitFactory* unitFactory);
    IBaseUnit* returnUnit(int index) { return _unitFactories[index]->create(nullptr);}

private:
    std::vector<std::pair<std::string,int>> _purchasableUnits;
    std::vector<IUnitFactory*> _unitFactories;
};


#endif //AGEOFWAR_BUYINGMANAGER_HPP