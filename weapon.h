#ifndef WEAPON_H
#define WEAPON_H
#include <QPixmap>
#include "config.h"

class Weapon
{
public:
    Weapon(int survivor_X, int survivor_Y);
//    virtual void updatePosition();
//    virtual void levelUp();

public:
    int level;

    QPixmap m_Weapon;

    int m_X;
    int m_Y;

    int m_Speed;
    int countDuration;

    QRect m_Rect;

};

#endif // WEAPON_H
