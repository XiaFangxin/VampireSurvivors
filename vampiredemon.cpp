#include "vampiredemon.h"

#include "config.h"

VampireDemon::VampireDemon()
{
    m_Vampire.load(DEMON_PATH);

    //初始化坐标
    random_counter += 114513;
    random_counter = random_counter % 10000000;

    m_X = (random_counter%2)*GAME_WIDTH;
    m_Y = random_counter%GAME_HEIGHT;

    //初始化矩形框
    m_Rect.setWidth(m_Vampire.width());
    m_Rect.setHeight(m_Vampire.height());
    m_Rect.moveTo(m_X,m_Y);

    HP = DEMON_BLOODVOLUMN;
    ATK = 1;

    m_direct = LEFT;
}

void VampireDemon::moveToTarget(int target_X, int target_Y)
{
    int instance_X = target_X-m_X;
    int instance_Y = target_Y-m_Y;
    if(instance_X > 0){
        m_X += 1;
        m_direct = RIGHT;
    }
    if(instance_X < 0){
        m_X -= 1;
        m_direct = LEFT;
    }
    if(instance_Y > 0)
        m_Y += 1;
    if(instance_Y < 0)
        m_Y -= 1;
}
