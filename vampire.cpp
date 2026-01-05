#include "vampire.h"
#include "config.h"
Vampire::Vampire()
{
}

void Vampire::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}

void Vampire::moveToTarget(int target_X, int target_Y)
{
    int instance_X = target_X-m_X;
    int instance_Y = target_Y-m_Y;
    if(instance_X > 0)
        m_X += 1;
    if(instance_X < 0)
        m_X -= 1;
    if(instance_Y > 0)
        m_Y += 1;
    if(instance_Y < 0)
        m_Y -= 1;
}

void Vampire::changeImage(int n)
{
    ;

}

void Vampire::beAttacked(int n){
    HP -= n;
}
