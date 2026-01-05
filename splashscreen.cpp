#include "splashscreen.h"
#include <QTextEdit>
#include <windows.h>
#include "config.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("Splash example;");
    QTextEdit *edit = new QTextEdit;
    edit->setText("Splash example1!");
    setCentralWidget(edit);
    resize(GAME_WIDTH, GAME_HEIGHT);
    Sleep(1000);
}
