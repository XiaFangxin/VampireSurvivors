#ifndef WEAPONFIRE_H
#define WEAPONFIRE_H

#include"weapon.h"
#include"config.h"


class WeaponFire:public Weapon
{
public:
    WeaponFire(int survivor_X, int survivor_Y);
    void changeImage(int n);

public:
    int ATK;
};

#endif // WEAPONFIRE_H
