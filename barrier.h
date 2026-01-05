#ifndef BARRIER_H
#define BARRIER_H

#include <QRect>
#include <QPixmap>

class Barrier
{
public:
    Barrier();
    void setPosition(int x, int y);

public:

    QPixmap m_Barrier;

    //障碍物坐标
    int m_X;
    int m_Y;

    //障碍物的矩形边框
    QRect m_Rect;
};

#endif // BARRIER_H
