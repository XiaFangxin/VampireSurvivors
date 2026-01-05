#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "mainscene.h"

class StartScene : public QMainWindow
{
    Q_OBJECT
public:

    explicit StartScene(QWidget *parent = nullptr);
    void initScene();

public:
    MainScene m_mainScene;

signals:
    void startGame();

signals:

};

#endif // STARTSCENE_H
