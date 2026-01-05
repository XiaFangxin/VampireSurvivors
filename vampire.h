#ifndef VAMPIRE_H
#define VAMPIRE_H

#include<QPixmap>

static int random_counter = 1;

class Vampire
{
public:
    Vampire();

    void setPosition(int x, int y);
    void moveToTarget(int target_X, int target_Y);
    virtual void changeImage(int n);
    void beAttacked(int n);

public:

    //吸血鬼资源 对象
    QPixmap m_Vampire;

    //吸血鬼坐标
    int m_X;
    int m_Y;

    //吸血鬼的矩形边框
    QRect m_Rect;

    //吸血鬼属性
    int HP;
    int ATK;
};

#endif // VAMPIRE_H
