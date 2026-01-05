#include "weaponice.h"

static int randomX = 1;
static int randomY = 1;

WeaponIce::WeaponIce():Weapon(0,0)
{
    m_Weapon.load(ICE_PATH0);

    m_Rect.setWidth(m_Weapon.width());
    m_Rect.setHeight(m_Weapon.height());

    randomX = (randomX*123)%GAME_WIDTH;
    randomY = (randomY*256)%GAME_HEIGHT;

    m_X = randomX;
    m_Y = randomY;

    m_Rect.moveTo(m_X,m_Y);

    ATK = 2;

    countDuration = 20;
}

void WeaponIce::changeImage(int n){
    switch(n%10){
    case(0):
        m_Weapon.load(ICE_PATH0);break;
    case(1):
        m_Weapon.load(ICE_PATH1);break;
    case(2):
        m_Weapon.load(ICE_PATH2);break;
    case(3):
        m_Weapon.load(ICE_PATH3);break;
    case(4):
        m_Weapon.load(ICE_PATH4);break;
    case(5):
        m_Weapon.load(ICE_PATH5);break;
    case(6):
        m_Weapon.load(ICE_PATH6);break;
    case(7):
        m_Weapon.load(ICE_PATH7);break;
    case(8):
        m_Weapon.load(ICE_PATH8);break;
    case(9):
        m_Weapon.load(ICE_PATH9);break;

    }
}
