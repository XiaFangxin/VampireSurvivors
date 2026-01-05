#include "weaponbullet.h"

WeaponBullet::WeaponBullet(int survivor_X, int survivor_Y, Direction survivor_direction):Weapon(survivor_X,survivor_Y)
{
    m_Weapon.load(BULLET_PATH);

    m_Rect.setWidth(m_Weapon.width());
    m_Rect.setHeight(m_Weapon.height());
    m_Rect.moveTo(m_X,m_Y);

    m_direct = survivor_direction;

    ATK = 1;
}

void WeaponBullet::updatePosition(){
    if(m_direct == UP)
        m_Y += m_Speed;
    if(m_direct == DOWN)
        m_Y -= m_Speed;
    if(m_direct == LEFT)
        m_X += m_Speed;
    if(m_direct == RIGHT)
        m_X -= m_Speed;
}

