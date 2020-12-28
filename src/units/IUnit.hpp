//
// Created by dominik on 12/27/20.
//

#ifndef AGEOFWAR_IUNIT_HPP
#define AGEOFWAR_IUNIT_HPP


#include <vector>

class IUnit {
public:
    int GetPrice() { return _price; }
    int GetHp() { return _hp; }
    int GetAttackPower() { return _attackPower; }
    bool IsPurchasable() { return _isPurchasable; }
    const std::vector<std::vector<int>> &GetPossibleRanges() { return _possibleRanges; }
    void GetDamage(int damage) { _hp -= damage; }

protected:
    int _price;
    int _hp;
    int _attackPower;
    bool _isPurchasable;
    std::vector<std::vector<int>> _possibleRanges;

private:

};
#endif //AGEOFWAR_IUNIT_HPP