//
// Created by dominik on 12/28/20.
//

#ifndef AGEOFWAR_IATTACKABLE_HPP
#define AGEOFWAR_IATTACKABLE_HPP


class IAttackable {
public:
    int GetHp() const { return m_hp; }
    int GetKillReward() const { return m_killReward; }

    void ReceiveDamage(int damage) { m_hp -= damage; }
protected:
    int m_hp;
    int m_killReward;
};


#endif //AGEOFWAR_IATTACKABLE_HPP
