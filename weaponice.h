#ifndef WEAPONICE_H
#define WEAPONICE_H

#include "weapon.h"

class WeaponIce:public Weapon
{
public:
    WeaponIce();
    void changeImage(int n);

public:

    int ATK;
};

#endif // WEAPONICE_H
