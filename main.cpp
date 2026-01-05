#include "mainscene.h"
#include "gamecontroller.h"
#include "config.h"
#include <QApplication>
#include <QResource>
#include <QSplashScreen>
#include <QThread>
#include <QPixmap>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameController m_game;

    return a.exec();
}

