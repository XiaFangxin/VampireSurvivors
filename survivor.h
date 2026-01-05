#ifndef SURVIVOR_H
#define SURVIVOR_H
#include <QPixmap>
#include <QRect>
#include "config.h"

class Survivor
{
public:
    Survivor();

    //设置幸存者位置
    void initSurvivor();
    void setPosition(int x, int y);
    void changeImage(int n);
    void changeRunImage(int n);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void beAttacked(int n);
    void addExp(int n);
    void addBlood();
    void revive();

public:
    //幸存者资源 对象
    QPixmap m_Survivor;

    //幸存者坐标
    int m_X;
    int m_Y;

    //幸存者的矩形边框
    QRect m_Rect;

    //幸存者状态
    bool isRunning;
    Direction m_direct;

    //幸存者属性
    int bloodVolumn;
    int HP;
    int level;
    int EXP;
};

#endif // SURVIVOR_H
