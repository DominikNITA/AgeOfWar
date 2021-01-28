#include <algorithm>
//
// Created by Dominik on 1/16/2021.
//

#include "BuyingManager.hpp"

std::vector<std::pair<std::string, int>> BuyingManager::getPurchasableUnits() {
    return m_purchasableUnits;
}

void BuyingManager::addUnit(const std::string& name, int price, IUnitFactory *unitFactory) {
    //https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back => no temporary object created
    m_minimalPrice = std::min(m_minimalPrice, price);
    m_purchasableUnits.emplace_back(name, price);
    m_unitFactories.push_back(unitFactory);
}

__unused std::string BuyingManager::getUnitNameByIndex(int index) {
    return m_purchasableUnits[index].first;
}
