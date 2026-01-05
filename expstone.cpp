#include "expstone.h"
#include "config.h"

ExpStone::ExpStone(int x, int y)
{
    m_ExpStone.load(EXPSTONE_PATH);

    //初始化坐标
    m_X = x;
    m_Y = y;

    //初始化矩形框
    m_Rect.setWidth(m_ExpStone.width());
    m_Rect.setHeight(m_ExpStone.height());
    m_Rect.moveTo(m_X,m_Y);

    m_exp = 1;
}
