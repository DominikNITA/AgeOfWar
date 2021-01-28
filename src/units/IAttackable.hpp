//
// Created by dominik on 12/28/20.
//

#ifndef AGEOFWAR_IATTACKABLE_HPP
#define AGEOFWAR_IATTACKABLE_HPP


class IAttackable {
public:
    int GetHp() const { return m_hp; }
    int GetKillReward() const { return m_killReward; }

    void receiveDamage(int damage) { m_hp -= damage; }
    void setHp(int newHp) { m_hp = newHp;}
protected:
    int m_hp;
    int m_killReward;
};


#endif //AGEOFWAR_IATTACKABLE_HPP
