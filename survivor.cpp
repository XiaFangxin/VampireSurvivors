#include "survivor.h"
#include "config.h"
#include <QDebug>

Survivor::Survivor()
{
    bloodVolumn = 500;
    initSurvivor();
}

void Survivor::initSurvivor(){
    m_Survivor.load(SURVIVOR_PATH0);

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 - m_Survivor.width()*0.5;
    m_Y = GAME_HEIGHT * 0.5 - m_Survivor.height()*0.5;

    //初始化矩形框
    m_Rect.setWidth(m_Survivor.width());
    m_Rect.setHeight(m_Survivor.height());
    m_Rect.moveTo(m_X,m_Y);

    isRunning = false;
    m_direct = UP;

    HP = bloodVolumn;
    EXP = 1;
}

void Survivor::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}

void Survivor::changeImage(int n){
    switch(n%6){
    case(0):
        m_Survivor.load(SURVIVOR_PATH0);break;
    case(1):
        m_Survivor.load(SURVIVOR_PATH1);break;
    case(2):
        m_Survivor.load(SURVIVOR_PATH2);break;
    case(3):
        m_Survivor.load(SURVIVOR_PATH3);break;
    case(4):
        m_Survivor.load(SURVIVOR_PATH4);break;
    case(5):
        m_Survivor.load(SURVIVOR_PATH5);break;
    }
}

void Survivor::changeRunImage(int n){
    switch(n%8){
    case(0):
        m_Survivor.load(SURVIVOR_RUN_PATH0);break;
    case(1):
        m_Survivor.load(SURVIVOR_RUN_PATH1);break;
    case(2):
        m_Survivor.load(SURVIVOR_RUN_PATH2);break;
    case(3):
        m_Survivor.load(SURVIVOR_RUN_PATH3);break;
    case(4):
        m_Survivor.load(SURVIVOR_RUN_PATH4);break;
    case(5):
        m_Survivor.load(SURVIVOR_RUN_PATH5);break;
    case(6):
        m_Survivor.load(SURVIVOR_RUN_PATH6);break;
    case(7):
        m_Survivor.load(SURVIVOR_RUN_PATH7);break;
    }
}

void Survivor::moveUp(){
    m_Y -= SURVIVOR_SPEED;
    m_Rect.moveTo(m_X,m_Y);
    m_direct = UP;
}

void Survivor::moveDown(){
    m_Y += SURVIVOR_SPEED;
    m_Rect.moveTo(m_X,m_Y);
    m_direct = DOWN;
}

void Survivor::moveLeft(){
    m_X -= SURVIVOR_SPEED;
    m_Rect.moveTo(m_X,m_Y);
    m_direct = LEFT;
}

void Survivor::moveRight(){
    m_X += SURVIVOR_SPEED;
    m_Rect.moveTo(m_X,m_Y);
    m_direct = RIGHT;
}

void Survivor::beAttacked(int n){
    m_Survivor.load(SURVIVOR_ATTACKED_PATH);
    HP -= n;
    qDebug() << HP;
}

void Survivor::addExp(int n){
    EXP += n;
}

void Survivor::addBlood(){
    HP += 100;
    if(HP >= bloodVolumn)
        HP = bloodVolumn;
}

void Survivor::revive(){
    HP = bloodVolumn;
}
