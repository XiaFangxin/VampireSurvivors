#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "map.h"
#include "survivor.h"
#include "barrier.h"
#include "weaponbullet.h"
#include "weaponfire.h"
#include "weaponice.h"
#include "vampirebat.h"
#include "vampireskeleton.h"
#include "vampiredemon.h"
#include "vlightning.h"
#include "expstone.h"
#include "gamedata.h"
#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QVector>

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(GameData* m_game_data, QWidget *parent = nullptr);
    ~MainScene();

    //启动游戏  用于启动定时器对象
    void playGame();

    //更新坐标
    void updatePosition();

    //绘图事件
    void paintEvent(QPaintEvent *event);

    //键盘事件
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void welcomeToGame();
    void succeedGame();
    void restartGame();
    void loseGame();
public slots:
    void initScene();

public:
    //地图对象
    Map m_map;

    //定时器
    QTimer m_Timer;

    //幸存者
    Survivor m_survivor;

    //键盘事件
    QList<int> keys;
    QTimer* keyRespondTimer;
    void slotTimeOut();

    //障碍物
    Barrier m_barrier[5];

    //吸血鬼
    QVector<VampireBat> m_bat_data;
    QVector<VampireSkeleton> m_ske_data;
    QVector<VampireDemon> m_demon_data;
    QVector<VLightning> m_lightning_data;

    //武器
    QVector<WeaponBullet> m_bullet_data;
    QVector<WeaponFire> m_fire_data;
    QVector<WeaponIce> m_ice_data;

    //经验石
    QVector<ExpStone> m_expstone_data;

    int pictureGlintCounter;

    GameData* m_game_data;

signals:
    void succeed();
    void restart();
    void levelUp();
    void gameLose();
};

#endif // MAINSCENE_H
