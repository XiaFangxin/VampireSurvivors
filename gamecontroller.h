#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "mainscene.h"
#include "gamedata.h"
#include <QVector>

class GameController:public QObject
{
public:
    GameController();

public:
    MainScene* m_main;
    GameData* m_game_data;
};

#endif // GAMECONTROLLER_H
