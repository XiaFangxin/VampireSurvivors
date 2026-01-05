#ifndef EXPSTONE_H
#define EXPSTONE_H

#include <QPixmap>

class ExpStone
{
public:
    ExpStone(int x, int y);

public:
    QPixmap m_ExpStone;

    int m_X;
    int m_Y;

    QRect m_Rect;

    int m_exp;
};

#endif // EXPSTONE_H
