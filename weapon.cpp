#include "weapon.h"

Weapon::Weapon(int survivor_X, int survivor_Y)
{
    m_X = survivor_X;
    m_Y = survivor_Y;
    m_Speed = WEAPON_SPEED;
    level = 1;
}
