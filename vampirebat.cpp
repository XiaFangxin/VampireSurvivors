#include "vampirebat.h"
#include "config.h"

VampireBat::VampireBat():Vampire()
{
    m_Vampire.load(BAT_PATH0);

    //初始化坐标
    random_counter += 114513;
    random_counter = random_counter % 10000000;
    switch(random_counter%4){
    case(0):
        m_X = 0;
        m_Y = random_counter%GAME_HEIGHT;break;
    case(1):
        m_Y = 0;
        m_X = random_counter%GAME_WIDTH;break;
    case(2):
        m_X = GAME_WIDTH;
        m_Y = random_counter%GAME_HEIGHT;break;
    case(3):
        m_Y = GAME_HEIGHT;
        m_X = random_counter%GAME_WIDTH;break;
    }

    //初始化矩形框
    m_Rect.setWidth(m_Vampire.width());
    m_Rect.setHeight(m_Vampire.height());
    m_Rect.moveTo(m_X,m_Y);

    HP = 1;
    ATK = 1;
}

void VampireBat::changeImage(int n){
    switch(n%11){
    case(0):
        m_Vampire.load(BAT_PATH0);break;
    case(1):
        m_Vampire.load(BAT_PATH1);break;
    case(2):
        m_Vampire.load(BAT_PATH2);break;
    case(3):
        m_Vampire.load(BAT_PATH3);break;
    case(4):
        m_Vampire.load(BAT_PATH4);break;
    case(5):
        m_Vampire.load(BAT_PATH5);break;
    case(6):
        m_Vampire.load(BAT_PATH6);break;
    case(7):
        m_Vampire.load(BAT_PATH7);break;
    case(8):
        m_Vampire.load(BAT_PATH8);break;
    case(9):
        m_Vampire.load(BAT_PATH9);break;
    case(10):
        m_Vampire.load(BAT_PATH10);break;
    }
}


