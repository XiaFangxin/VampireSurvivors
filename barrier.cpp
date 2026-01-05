#include "barrier.h"
#include "config.h"
#include <QDebug>

Barrier::Barrier()
{
    //初始化加载障碍物图片资源
    m_Barrier.load(BARRIER_PATH);

    //初始化坐标
    m_X = 300;
    m_Y = 600;

    //初始化矩形框
    m_Rect.setWidth(m_Barrier.width());
    m_Rect.setHeight(m_Barrier.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Barrier::setPosition(int x, int y){
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}
