//
// Created by dominik on 12/28/20.
//

#ifndef AGEOFWAR_IATTACKABLE_HPP
#define AGEOFWAR_IATTACKABLE_HPP


class IAttackable {
public:
    int GetHp() const { return _hp; }
    int GetKillReward() const { return _killReward; }

    void ReceiveDamage(int damage) { _hp -= damage; }
protected:
    int _hp;
    int _killReward;
};


#endif //AGEOFWAR_IATTACKABLE_HPP
