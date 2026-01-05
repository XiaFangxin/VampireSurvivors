#include "startscene.h"
#include "config.h"
#include <qapplication.h>
#include <qpushbutton.h>
#include <QDebug>
#include <qfont.h>

StartScene::StartScene(QWidget *parent)
    : QMainWindow{parent}
{
    initScene();
}

void StartScene::initScene(){
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon( GAME_ICON));

    QPushButton *startBtn = new QPushButton("START", this);
    startBtn->setGeometry(GAME_WIDTH/2-200,GAME_HEIGHT/2-150,400,300);
    startBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));


    connect(startBtn, &QPushButton::clicked, [=](){
        this->close();
        m_mainScene.show();
        m_mainScene.initScene();
    });

    connect(&m_mainScene, &MainScene::succeed, [=](){
        qDebug() << "succeed";
        m_mainScene.close();
        this->show();
        QPushButton *restartBtn = new QPushButton("RESTART", this);
        restartBtn->setGeometry(GAME_WIDTH/2-200,GAME_HEIGHT/2-150,400,300);
        restartBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
        connect(restartBtn,&QPushButton::clicked,[=](){
            m_mainScene.show();
            m_mainScene.initScene();
        });
    });

}
