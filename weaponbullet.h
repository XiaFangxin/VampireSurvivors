#ifndef WEAPONBULLET_H
#define WEAPONBULLET_H
#include "weapon.h"

class WeaponBullet:public Weapon
{
public:
    WeaponBullet(int survivor_X, int survivor_Y, Direction survivor_direct);
    void updatePosition();

public:
    Direction m_direct;
    int ATK;
};

#endif // WEAPONBULLET_H
