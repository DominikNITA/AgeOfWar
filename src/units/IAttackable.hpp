//
// Created by dominik on 12/28/20.
//

#ifndef AGEOFWAR_IATTACKABLE_HPP
#define AGEOFWAR_IATTACKABLE_HPP


class IAttackable {
public:
    int GetHp() { return _hp; }
    void GetDamage(int damage) { _hp -= damage; }
    int GetKillReward() { return _killReward; }
protected:
    int _hp;
    int _killReward;
};


#endif //AGEOFWAR_IATTACKABLE_HPP
