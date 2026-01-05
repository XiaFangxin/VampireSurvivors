#include "vampireskeleton.h"
#include "config.h"

VampireSkeleton::VampireSkeleton()
{
    m_Vampire.load(SKE_PATH0);

    //初始化坐标
    random_counter += 114513;
    random_counter = random_counter % 10000000;

    m_X = random_counter%GAME_WIDTH;
    m_Y = random_counter%GAME_HEIGHT;

    //初始化矩形框
    m_Rect.setWidth(m_Vampire.width());
    m_Rect.setHeight(m_Vampire.height());
    m_Rect.moveTo(m_X,m_Y);

    HP = 1;
    ATK = 3;
    countDuration = 27;
}

void VampireSkeleton::changePosition(){
    if(countDuration <= 10 && countDuration >= 2){
        m_X += SKE_SPEED;
        if(countDuration == 5 || countDuration == 6)
            m_X += SKE_SPEED*3;
       m_Rect.moveTo(m_X,m_Y);
    }
    countDuration--;
}

void VampireSkeleton::changeImage(){
    switch(27-countDuration){
    case(0):
        m_Vampire.load(SKE_PATH0);break;
    case(1):
        m_Vampire.load(SKE_PATH1);break;
    case(2):
        m_Vampire.load(SKE_PATH2);break;
    case(3):
        m_Vampire.load(SKE_PATH3);break;
    case(4):
        m_Vampire.load(SKE_PATH4);break;
    case(5):
        m_Vampire.load(SKE_PATH5);break;
    case(6):
        m_Vampire.load(SKE_PATH6);break;
    case(7):
        m_Vampire.load(SKE_PATH7);break;
    case(8):
        m_Vampire.load(SKE_PATH8);break;
    case(9):
        m_Vampire.load(SKE_PATH9);break;
    case(10):
        m_Vampire.load(SKE_PATH10);break;
    case(11):
        m_Vampire.load(SKE_PATH11);break;
    case(12):
        m_Vampire.load(SKE_PATH12);break;
    case(13):
        m_Vampire.load(SKE_PATH13);break;
    case(14):
        m_Vampire.load(SKE_PATH14);break;
    case(15):
        m_Vampire.load(SKE_RUN_PATH0);break;
    case(16):
        m_Vampire.load(SKE_RUN_PATH1);break;
    case(17):
        m_Vampire.load(SKE_RUN_PATH2);break;
    case(18):
        m_Vampire.load(SKE_RUN_PATH3);break;
    case(19):
        m_Vampire.load(SKE_RUN_PATH4);break;
    case(20):
        m_Vampire.load(SKE_RUN_PATH5);break;
    case(21):
        m_Vampire.load(SKE_RUN_PATH6);break;
    case(22):
        m_Vampire.load(SKE_RUN_PATH7);break;
    case(23):
        m_Vampire.load(SKE_RUN_PATH8);break;
    case(24):
        m_Vampire.load(SKE_RUN_PATH9);break;
    case(25):
        m_Vampire.load(SKE_RUN_PATH10);break;
    case(26):
        m_Vampire.load(SKE_RUN_PATH11);break;
    }
}
