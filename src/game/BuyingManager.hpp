#include <algorithm>
//
// Created by Dominik on 1/16/2021.
//

#ifndef AGEOFWAR_BUYINGMANAGER_HPP
#define AGEOFWAR_BUYINGMANAGER_HPP

#include <vector>
#include "UnitFactory.hpp"


class BuyingManager {
public:
    BuyingManager() = default;
    std::vector<std::pair<std::string,int>> getPurchasableUnits();
    void addUnit(const std::string&, int price, IUnitFactory* unitFactory);
    std::shared_ptr<IBaseUnit> returnUnit(int index) { return m_unitFactories[index]->create(nullptr);}
    int getMinimalPrice() const {return m_minimalPrice;}

    __unused std::string getUnitNameByIndex(int index);

private:
    std::vector<std::pair<std::string,int>> m_purchasableUnits;
    std::vector<IUnitFactory*> m_unitFactories;
    int m_minimalPrice = INT8_MAX;
};


#endif //AGEOFWAR_BUYINGMANAGER_HPP
