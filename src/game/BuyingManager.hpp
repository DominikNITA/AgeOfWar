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
    // Default constructor
    BuyingManager() = default;

    /// Add unit entry to the list
    /// \param price
    /// \param unitFactory
    void addUnit(const std::string&, int price, IUnitFactory* unitFactory);

    /// Get vector of pairs of purchasable units defined by display name and price
    /// \return
    std::vector<std::pair<std::string,int>> getPurchasableUnits();

    ///
    /// \param index
    /// \return unit from selected index
    std::shared_ptr<IBaseUnit> createUnit(int index) { return m_unitFactories[index]->create(nullptr);}

    ///
    /// \return Cost of the cheapest unit
    int getMinimalPrice() const {return m_minimalPrice;}

private:
    std::vector<std::pair<std::string,int>> m_purchasableUnits;
    std::vector<IUnitFactory*> m_unitFactories;
    int m_minimalPrice = INT8_MAX; //Cost of the cheapest unit
};


#endif //AGEOFWAR_BUYINGMANAGER_HPP