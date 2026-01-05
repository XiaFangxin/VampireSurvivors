#include "vlightning.h"

#include "config.h"

VLightning::VLightning(int m, int n, Direction m_direct):m_direct(m_direct)
{
    m_Vampire.load(LIGHTNING_PATH0);

    m_X = m;
    m_Y = n;
    if(m_direct == LEFT)
        m_X -= 20;
    else
        m_X += 20;

    //初始化矩形框
    m_Rect.setWidth(m_Vampire.width());
    m_Rect.setHeight(m_Vampire.height());
    m_Rect.moveTo(m_X,m_Y);

    HP = 1;
    ATK = 1;

    countDuration = 8;
}

void VLightning::changeImage(){
    switch(8-countDuration){
    case(0):
        m_Vampire.load(LIGHTNING_PATH0);break;
    case(1):
        m_Vampire.load(LIGHTNING_PATH1);break;
    case(2):
        m_Vampire.load(LIGHTNING_PATH2);break;
    case(3):
        m_Vampire.load(LIGHTNING_PATH3);break;
    case(4):
        m_Vampire.load(LIGHTNING_PATH4);break;
    case(5):
        m_Vampire.load(LIGHTNING_PATH5);break;
    case(6):
        m_Vampire.load(LIGHTNING_PATH6);break;
    case(7):
        m_Vampire.load(LIGHTNING_PATH7);break;
    }
    countDuration--;
}

void VLightning::changePosition(){
    switch(m_direct){
    case(LEFT):
        m_X -= LIGHTNING_SPEED;break;
    case(RIGHT):
        m_X += LIGHTNING_SPEED;break;
    }
    m_Rect.moveTo(m_X, m_Y);
}
