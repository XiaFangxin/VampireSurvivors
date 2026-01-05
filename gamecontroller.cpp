#include "gamecontroller.h"

#include <QObject>
#include <QPushButton>

GameController::GameController()
{
    m_game_data = new GameData();
    m_main = new MainScene(m_game_data);
    m_main->show();

}
