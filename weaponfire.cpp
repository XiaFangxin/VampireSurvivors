#include "weaponfire.h"

#include "config.h"

WeaponFire::WeaponFire(int survivor_X, int survivor_Y):Weapon(survivor_X,survivor_Y)
{
    m_Weapon.load(FIRE_PATH0);

    m_Rect.setWidth(m_Weapon.width());
    m_Rect.setHeight(m_Weapon.height());
    m_Rect.moveTo(m_X,m_Y);

    ATK = 2;

    countDuration = 17;
}

void WeaponFire::changeImage(int n){
    switch(n%17){
    case(0):
        m_Weapon.load(FIRE_PATH0);break;
    case(1):
        m_Weapon.load(FIRE_PATH1);break;
    case(2):
        m_Weapon.load(FIRE_PATH2);break;
    case(3):
        m_Weapon.load(FIRE_PATH3);break;
    case(4):
        m_Weapon.load(FIRE_PATH4);break;
    case(5):
        m_Weapon.load(FIRE_PATH5);break;
    case(6):
        m_Weapon.load(FIRE_PATH6);break;
    case(7):
        m_Weapon.load(FIRE_PATH7);break;
    case(8):
        m_Weapon.load(FIRE_PATH8);break;
    case(9):
        m_Weapon.load(FIRE_PATH9);break;
    case(10):
        m_Weapon.load(FIRE_PATH10);break;
    case(11):
        m_Weapon.load(FIRE_PATH11);break;
    case(12):
        m_Weapon.load(FIRE_PATH12);break;
    case(13):
        m_Weapon.load(FIRE_PATH13);break;
    case(14):
        m_Weapon.load(FIRE_PATH14);break;
    case(15):
        m_Weapon.load(FIRE_PATH15);break;
    case(16):
        m_Weapon.load(FIRE_PATH16);break;
    }
}
