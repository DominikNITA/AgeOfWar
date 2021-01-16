//
// Created by Dominik on 1/16/2021.
//

#include "BuyingManager.hpp"

std::vector<std::pair<char *, int>> BuyingManager::getPurchasableUnits() {
    return _purchasableUnits;
}

void BuyingManager::addUnit(char *name, int price, IUnitFactory *unitFactory) {
    //https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back => no temporary object created
    _purchasableUnits.emplace_back(name,price);
    _unitFactories.push_back(unitFactory);
}
