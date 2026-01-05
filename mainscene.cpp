#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QDebug>
#include <QTime>
#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>>

MainScene::MainScene(GameData* m_game_data, QWidget *parent)
    : QMainWindow(parent),m_game_data(m_game_data)
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon( GAME_ICON));

    //设置常驻商城
    QPushButton* shopBtn = new QPushButton("SHOP", this);
    shopBtn->setGeometry(GAME_WIDTH-200,50,150,100);
    shopBtn->setFont(QFont("微软雅黑", 14, QFont::Bold));
    shopBtn->setStyleSheet("color:#F0FFFF;background-color:#6FDCDCDC;"
                           "border-radius: 50px;");
    shopBtn->show();

    QLabel* shopBackground = new QLabel(this);
    shopBackground->setStyleSheet("color:#F0FFFF;background-color:#b4c9df;"
                                  "border: 4px groove #F0FFFF; border-radius: 80px;");
    shopBackground->setGeometry(GAME_WIDTH/2-500, 400, 1000, 800);
    shopBackground->close();

    QPushButton* shopBack = new QPushButton("BACK", this);
    shopBack->setGeometry(GAME_WIDTH/2-100, 1000, 200, 100);
    shopBack->setFont(QFont("微软雅黑", 14, QFont::Bold));
    shopBack->setStyleSheet("color:#F0FFFF;background-color:#6FDCDCDC;"
                           "border-radius: 50px;");
    shopBack->close();

    QPushButton* buyRevival = new QPushButton("BUY A REVIVAL CHANCE", this);
    buyRevival->setGeometry(GAME_WIDTH/2-300, 600, 600, 200);
    buyRevival->setFont(QFont("微软雅黑", 14, QFont::Bold));
    buyRevival->setStyleSheet("color:#333333;background-color:#6FDCDCDC;"
                           "border-radius: 50px;");
    buyRevival->close();

    QString coinNum = QString("%1").arg(m_game_data->coin);
    QString revivalNum = QString("%1").arg(m_game_data->revivalNum);
    QLabel* showCoin = new QLabel(this);
    showCoin->setText("  coin: "+coinNum+"\trevival times: "+revivalNum);
    showCoin->setFont(QFont("微软雅黑", 14, QFont::Bold));
    showCoin->setStyleSheet("color:#333333;background-color:transparent;");
    showCoin->setGeometry(GAME_WIDTH/2-300, 820, 600, 50);
    showCoin->close();

    connect(shopBtn, &QPushButton::clicked, this, [=](){
        shopBtn->close();
        shopBackground->show();
        shopBackground->raise();
        shopBack->show();
        shopBack->raise();
        buyRevival->show();
        buyRevival->raise();
        showCoin->show();
        showCoin->raise();
    });

    connect(buyRevival, &QPushButton::clicked, this, [=](){
        if(m_game_data->coin >= REVIVAL_PRICE){
            m_game_data->coin -= REVIVAL_PRICE;
            m_game_data->revivalNum += 1;
            qDebug() << "buy!";
            QString coinNum = QString("%1").arg(m_game_data->coin);
            QString revivalNum = QString("%1").arg(m_game_data->revivalNum);
            showCoin->setText("  coin: "+coinNum+"\trevival times: "+revivalNum);
        }
    });

    connect(shopBack, &QPushButton::clicked, this, [=](){
        shopBtn->show();
        shopBackground->close();
        shopBack->close();
        buyRevival->close();
        showCoin->close();
    });
    //开始游戏界面
    welcomeToGame();
}

MainScene::~MainScene()
{

}

void MainScene::welcomeToGame(){
    QPushButton *startBtn = new QPushButton("START", this);
    startBtn->setGeometry(750,700,500,150);
    startBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
    startBtn->setStyleSheet("background-color:#DFDCDCDC;"
                            "border-radius: 50px;");
    startBtn->show();

    QLabel* signalWelcome = new QLabel(this);
    signalWelcome ->resize(500, 200);
    signalWelcome ->move(750, 400);
    signalWelcome ->setText("Welcome!");
    signalWelcome ->setStyleSheet("color:aqua");
    signalWelcome ->setFont(QFont("STCaiyun", 40, QFont::Bold));
    signalWelcome->show();

    connect(startBtn, &QPushButton::clicked, [=](){
        startBtn->deleteLater();
        this->initScene();
        signalWelcome->close();
    });
}

void MainScene::initScene(){
    //定时器设置
    m_Timer.setInterval(GAME_RATE);

    //响应按键设置
    setFocusPolicy(Qt::StrongFocus);

    keyRespondTimer = new QTimer(this);	//构造函数中创建定时器对象，并连接信号槽
    connect(keyRespondTimer, &QTimer::timeout, this, &MainScene::slotTimeOut);

    pictureGlintCounter = 0;

    //障碍物设置
    m_barrier[0].setPosition(200,300);
    m_barrier[1].setPosition(300,1000);
    m_barrier[2].setPosition(700,400);
    m_barrier[3].setPosition(500,500);
    m_barrier[4].setPosition(1400,700);

    playGame();
}

void MainScene::playGame()
{
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){

        //更新游戏中元素的坐标
        updatePosition();

        //重新绘制图片
        update();

        //幸存者状态图片绘制
        if(!m_survivor.isRunning){
            if(pictureGlintCounter%20 == 0){
                //            qDebug() << pictureGlintCounter/20;
                m_survivor.changeImage(pictureGlintCounter/20);
            }
        }
        else{
            if(pictureGlintCounter%20 == 0){
                m_survivor.changeRunImage(pictureGlintCounter/20);
            }
        }

        //幸存者受到伤害检测
        for(QVector<VampireBat>::iterator iter = m_bat_data.begin(); iter != m_bat_data.end();iter++){
            if(iter->m_X+iter->m_Rect.width() >= m_survivor.m_X+50 && iter->m_X <= m_survivor.m_X+m_survivor.m_Rect.width()-50
                && iter->m_Y+iter->m_Rect.height() >= m_survivor.m_Y+50 && iter->m_Y <= m_survivor.m_Y+m_survivor.m_Rect.height()-50){
                m_survivor.beAttacked(iter->ATK);
                if(m_survivor.HP <= 0)
                    emit gameLose();
            }
        }
        for(QVector<VampireSkeleton>::iterator iter = m_ske_data.begin(); iter != m_ske_data.end();iter++){
            if(iter->m_X+iter->m_Rect.width() >= m_survivor.m_X+50 && iter->m_X <= m_survivor.m_X+m_survivor.m_Rect.width()-50
                && iter->m_Y+iter->m_Rect.height() >= m_survivor.m_Y+50 && iter->m_Y <= m_survivor.m_Y+m_survivor.m_Rect.height()-50)
                {m_survivor.beAttacked(iter->ATK);
                if(m_survivor.HP <= 0)
                    emit gameLose();
            }
        }
        for(QVector<VampireDemon>::iterator iter = m_demon_data.begin(); iter != m_demon_data.end();iter++){
            if(iter->m_X+iter->m_Rect.width() >= m_survivor.m_X+50 && iter->m_X <= m_survivor.m_X+m_survivor.m_Rect.width()-50
                && iter->m_Y+iter->m_Rect.height() >= m_survivor.m_Y+50 && iter->m_Y <= m_survivor.m_Y+m_survivor.m_Rect.height()-50)
            {m_survivor.beAttacked(iter->ATK);
                if(m_survivor.HP <= 0)
                    emit gameLose();
            }
        }
        for(QVector<VLightning>::iterator iter = m_lightning_data.begin(); iter != m_lightning_data.end();iter++){
            if(iter->m_X+iter->m_Rect.width() >= m_survivor.m_X+50 && iter->m_X <= m_survivor.m_X+m_survivor.m_Rect.width()-50
                && iter->m_Y+iter->m_Rect.height() >= m_survivor.m_Y+50 && iter->m_Y <= m_survivor.m_Y+m_survivor.m_Rect.height()-50)
            {m_survivor.beAttacked(iter->ATK);
                if(m_survivor.HP <= 0)
                    emit gameLose();
            }
        }

        //幸存者吸收经验石
        for(QVector<ExpStone>::iterator iter = m_expstone_data.begin(); iter != m_expstone_data.end();iter++){
            if(iter->m_X >= m_survivor.m_X-m_survivor.m_Rect.width() && iter->m_X <= m_survivor.m_X
                && iter->m_Y >= m_survivor.m_Y-m_survivor.m_Y+m_survivor.m_Rect.height() && iter->m_Y >= m_survivor.m_Y){
                m_survivor.addExp(iter->m_exp);
                if(m_survivor.EXP%4 == 0)
                    emit levelUp();
                m_expstone_data.erase(iter);
                break;
            }
        }

        //吸血鬼Bat图片绘制
        if(pictureGlintCounter%20 == 0){
            for(QVector<VampireBat>::iterator iter = m_bat_data.begin(); iter != m_bat_data.end();iter++){
                iter->changeImage(pictureGlintCounter/20);
            }
        }

        //吸血鬼Bat移动
        for(QVector<VampireBat>::iterator iter = m_bat_data.begin(); iter != m_bat_data.end();iter++){
            iter->moveToTarget(m_survivor.m_X+m_survivor.m_Rect.width()/4, m_survivor.m_Y+m_survivor.m_Rect.height()/2);
        }

        //创建在地图上的吸血鬼Bat
        if(pictureGlintCounter%m_game_data->bat_interval == 0){
            VampireBat* newBat = new VampireBat();
            m_bat_data.push_back(*newBat);
        }

        //吸血鬼Bat受到伤害检测,是否落下经验石
        for(QVector<VampireBat>::iterator iterBat = m_bat_data.begin(); iterBat != m_bat_data.end();iterBat++){
            bool check = false;
            for(QVector<WeaponBullet>::iterator iterBullet = m_bullet_data.begin(); iterBullet != m_bullet_data.end();iterBullet++){
                if(iterBullet->m_X >= iterBat->m_X && iterBullet->m_X <= (iterBat->m_X+iterBat->m_Rect.width())
                    && iterBullet->m_Y >= iterBat->m_Y && iterBullet->m_Y <= (iterBat->m_Y+iterBat->m_Rect.height())){
                    iterBat->beAttacked(iterBullet->ATK);
                    if(iterBat->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterBat->m_X, iterBat->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_bat_data.erase(iterBat);
                        check = true;
                        break;
                    }
                }
            }
            for(QVector<WeaponFire>::iterator iterFire = m_fire_data.begin(); iterFire != m_fire_data.end(); iterFire++){
                if(iterFire->m_X >= iterBat->m_X && iterFire->m_X <= (iterBat->m_X+iterBat->m_Rect.width())
                    && iterFire->m_Y >= iterBat->m_Y && iterFire->m_Y <= (iterBat->m_Y+iterBat->m_Rect.height())){
                    iterBat->beAttacked(iterFire->ATK);
                    if(iterBat->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterBat->m_X, iterBat->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_bat_data.erase(iterBat);
                        check = true;
                        break;
                    }
                }
            }
            if(check)
                break;
        }

        //吸血鬼Skeleton图片绘制和移动
        if(pictureGlintCounter%10 == 0){
            for(QVector<VampireSkeleton>::iterator iter = m_ske_data.begin(); iter != m_ske_data.end();iter++){
                iter->changeImage();
                iter->changePosition();
            }
        }

        //创建在地图上的吸血鬼Skeleton
        if(pictureGlintCounter%m_game_data->ske_interval == 0){
            VampireSkeleton* newSke = new VampireSkeleton();
            m_ske_data.push_back(*newSke);
        }

        //吸血鬼Skeleton超过周期自动消亡
        for(QVector<VampireSkeleton>::iterator iter = m_ske_data.begin(); iter != m_ske_data.end();iter++){
            if(iter->countDuration <= 0){
                m_ske_data.erase(iter);
                break;
            }
        }

        //吸血鬼Skeleton受到伤害检测,是否落下经验石
        for(QVector<VampireSkeleton>::iterator iterSke = m_ske_data.begin(); iterSke != m_ske_data.end();iterSke++){
            bool check = false;
            for(QVector<WeaponBullet>::iterator iterBullet = m_bullet_data.begin(); iterBullet != m_bullet_data.end();iterBullet++){
                if(iterBullet->m_X >= iterSke->m_X+20 && iterBullet->m_X+iterBullet->m_Rect.width() <= (iterSke->m_X+iterSke->m_Rect.width()-20)
                    && iterBullet->m_Y >= iterSke->m_Y+20 && iterBullet->m_Y+iterBullet->m_Rect.height() <= (iterSke->m_Y+iterSke->m_Rect.height()-20)){
                    iterSke->beAttacked(iterBullet->ATK);
                    if(iterSke->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterSke->m_X, iterSke->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_ske_data.erase(iterSke);
                        check = true;
                        break;
                    }
                }
            }
            for(QVector<WeaponFire>::iterator iterFire = m_fire_data.begin(); iterFire != m_fire_data.end(); iterFire++){
                if(iterFire->m_X >= iterSke->m_X+20 && iterFire->m_X+iterFire->m_Rect.width() <= (iterSke->m_X+iterSke->m_Rect.width()-20)
                    && iterFire->m_Y >= iterSke->m_Y+20 && iterFire->m_Y+iterFire->m_Rect.height() <= (iterSke->m_Y+iterSke->m_Rect.height()-20)){
                    iterSke->beAttacked(iterFire->ATK);
                    if(iterSke->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterSke->m_X, iterSke->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_ske_data.erase(iterSke);
                        check = true;
                        break;
                    }
                }
            }
            if(check)
                break;
        }

        //吸血鬼Demon移动
        if(pictureGlintCounter%2)
            for(QVector<VampireDemon>::iterator iter = m_demon_data.begin(); iter != m_demon_data.end();iter++){
                iter->moveToTarget(m_survivor.m_X+m_survivor.m_Rect.width()/4, m_survivor.m_Y+m_survivor.m_Rect.height()/2);
            }

        //创建在地图上的吸血鬼Demon
        if(pictureGlintCounter%m_game_data->demon_interval == 0){
            VampireDemon* newDemon = new VampireDemon();
            m_demon_data.push_back(*newDemon);
        }

        //吸血鬼Demon远程释放雷电VLightning技能
        if(pictureGlintCounter%LIGHTNING_INTERVAL == 0){
            for(QVector<VampireDemon>::iterator iter = m_demon_data.begin(); iter != m_demon_data.end();iter++){
                VLightning* newLightning = new VLightning(iter->m_X, iter->m_Y, iter->m_direct) ;
                m_lightning_data.push_back(*newLightning);
            }
        }

        //雷电VLightning的移动和图片绘制
        if(pictureGlintCounter%10 == 0){
            for(QVector<VLightning>::iterator iter = m_lightning_data.begin(); iter != m_lightning_data.end();iter++){
                iter->changeImage();
                iter->changePosition();
            }
        }

        //雷电Lightning超过周期自动消亡
        for(QVector<VLightning>::iterator iter = m_lightning_data.begin(); iter != m_lightning_data.end();iter++){
            if(iter->countDuration <= 0){
                m_lightning_data.erase(iter);
                break;
            }
        }

        //吸血鬼Demon受到伤害检测,是否落下经验石
        for(QVector<VampireDemon>::iterator iterDemon = m_demon_data.begin(); iterDemon != m_demon_data.end();iterDemon++){
            bool check = false;
            for(QVector<WeaponBullet>::iterator iterBullet = m_bullet_data.begin(); iterBullet != m_bullet_data.end();iterBullet++){
                if(iterBullet->m_X >= iterDemon->m_X+20 && iterBullet->m_X+iterBullet->m_Rect.width() <= (iterDemon->m_X+iterDemon->m_Rect.width()-20)
                    && iterBullet->m_Y >= iterDemon->m_Y+20 && iterBullet->m_Y+iterBullet->m_Rect.height() <= (iterDemon->m_Y+iterDemon->m_Rect.height()-20)){
                    iterDemon->beAttacked(iterBullet->ATK);
                    if(iterDemon->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterDemon->m_X, iterDemon->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_demon_data.erase(iterDemon);
                        check = true;
                        break;
                    }
                }
            }
            for(QVector<WeaponFire>::iterator iterFire = m_fire_data.begin(); iterFire != m_fire_data.end(); iterFire++){
                if(iterFire->m_X >= iterDemon->m_X+20 && iterFire->m_X+iterFire->m_Rect.width() <= (iterDemon->m_X+iterDemon->m_Rect.width()-20)
                    && iterFire->m_Y >= iterDemon->m_Y+20 && iterFire->m_Y+iterFire->m_Rect.height() <= (iterDemon->m_Y+iterDemon->m_Rect.height()-20)){
                    iterDemon->beAttacked(iterFire->ATK);
                    if(iterDemon->HP <= 0){
                        ExpStone* newStone = new ExpStone(iterDemon->m_X, iterDemon->m_Y);
                        m_expstone_data.push_back(*newStone);
                        m_demon_data.erase(iterDemon);
                        check = true;
                        break;
                    }
                }
            }
            if(check)
                break;
        }


        //武器Bullet移动
        for(QVector<WeaponBullet>::iterator iter = m_bullet_data.begin(); iter != m_bullet_data.end();iter++){
            iter->updatePosition();
        }

        //创建在地图上的武器Bullet，以及其在Duration后消失
        if(pictureGlintCounter%m_game_data->bullet_interval == 0){
            if(pictureGlintCounter>= m_game_data->bullet_duration)
                m_bullet_data.pop_front();
            WeaponBullet* newBullet = new WeaponBullet(m_survivor.m_X+m_survivor.m_Rect.width()/2, m_survivor.m_Y+m_survivor.m_Rect.height()/2,m_survivor.m_direct);
            m_bullet_data.push_back(*newBullet);
        }

        //武器Fire图片绘制
        if(pictureGlintCounter%20 == 0){
            for(QVector<WeaponFire>::iterator iter = m_fire_data.begin(); iter != m_fire_data.end();iter++){
                iter->changeImage(pictureGlintCounter/20);
            }
        }

        //Fire过了duration就会消失
        if(pictureGlintCounter%10 == 0){
            for(QVector<WeaponFire>::iterator iter = m_fire_data.begin(); iter != m_fire_data.end();iter++){
                iter->countDuration--;
            }
            if(m_fire_data.size()){
                if(m_fire_data.begin()->countDuration <= 0){
                    for(int i = 0; i < 16; i++)
                        m_fire_data.pop_front();
                }
            }
        }

        //创建在地图上的武器Fire
        if(pictureGlintCounter%(m_game_data->fire_interval) == 0){
            for(int i = 1; i < 5; i++){
                WeaponFire* newFire1 = new WeaponFire(m_survivor.m_X+m_survivor.m_Rect.width()/4+80*i, m_survivor.m_Y+m_survivor.m_Rect.height()/4);
                m_fire_data.push_back(*newFire1);
                WeaponFire* newFire2 = new WeaponFire(m_survivor.m_X+m_survivor.m_Rect.width()/4-80*i, m_survivor.m_Y+m_survivor.m_Rect.height()/4);
                m_fire_data.push_back(*newFire2);
                WeaponFire* newFire3 = new WeaponFire(m_survivor.m_X+m_survivor.m_Rect.width()/4, m_survivor.m_Y+m_survivor.m_Rect.height()/4-80*i);
                m_fire_data.push_back(*newFire3);
                WeaponFire* newFire4 = new WeaponFire(m_survivor.m_X+m_survivor.m_Rect.width()/4, m_survivor.m_Y+m_survivor.m_Rect.height()/4+80*i);
                m_fire_data.push_back(*newFire4);
            }
        }

        //武器Ice图片绘制
        if(pictureGlintCounter%20 == 0){
            for(QVector<WeaponIce>::iterator iter = m_ice_data.begin(); iter != m_ice_data.end();iter++){
                iter->changeImage(pictureGlintCounter/20);
            }
        }

        //Ice过了duration就会消失
        if(pictureGlintCounter%10 == 0){
            for(QVector<WeaponIce>::iterator iter = m_ice_data.begin(); iter != m_ice_data.end();iter++){
                iter->countDuration--;
            }
            if(m_ice_data.size()){
                if(m_ice_data.begin()->countDuration <= 0){
                    for(int i = 0; i < m_game_data->ice_num; i++)
                        m_ice_data.pop_front();
                }
            }
        }

        //创建在地图上的武器Ice
        if(pictureGlintCounter%(m_game_data->ice_interval) == 0){
            for(int i = 0; i < m_game_data->ice_num; i++){
                WeaponIce *newIce = new WeaponIce;
                m_ice_data.push_back(*newIce);
            }
        }

        //对pictureGlintCounter计数
        pictureGlintCounter++;

        if(pictureGlintCounter*GAME_RATE >= 1000*GAME_TIME_DURATION){
            m_Timer.stop();
            emit succeed();
        }
    });

    //游戏胜利检测
    connect(this, &MainScene::succeed, this, [=](){
        succeedGame();
    });

    //游戏失败和重生检测
    QPushButton* revivalBtn = new QPushButton("revive", this);
    QPushButton* revivalNotBtn = new QPushButton("not revive", this);
    QLabel* revivalSignal = new QLabel(this);
    revivalBtn->setGeometry(750,700,500,150);
    revivalBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
    revivalBtn->setStyleSheet("background-color:#DFDCDCDC;"
                              "border-radius: 50px;");

    revivalNotBtn->setGeometry(750,900,500,150);
    revivalNotBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
    revivalNotBtn->setStyleSheet("background-color:#DFDCDCDC;"
                                 "border-radius: 50px;");

    revivalSignal ->resize(1500, 200);
    revivalSignal ->move(450, 400);
    revivalSignal ->setText("You have a chance to revive!");
    revivalSignal ->setStyleSheet("color:aqua");
    revivalSignal ->setFont(QFont("STCaiyun", 35, QFont::Bold));

    connect(this, &MainScene::gameLose, this, [=](){
        m_Timer.stop();
        if(m_game_data->haveRevivaled == false && m_game_data->revivalNum > 0){
            revivalBtn->show();
            revivalNotBtn->show();
            revivalSignal->show();
        }
        else
            loseGame();
    });

    connect(revivalBtn, &QPushButton::clicked, this, [=](){
        m_Timer.start();
        m_game_data->haveRevivaled = true;
        m_game_data->revivalNum -= 1;
        revivalBtn->close();
        revivalNotBtn->close();
        revivalSignal->close();
        m_survivor.revive();
    });

    connect(revivalNotBtn, &QPushButton::clicked, this, [=](){
        revivalBtn->close();
        revivalNotBtn->close();
        revivalSignal->close();
        loseGame();
    });

    //武器升级检测
    QLabel* signalLevelUp = new QLabel(this);
    signalLevelUp->resize(500, 500);
    signalLevelUp->move(750, 300);
    signalLevelUp->setText("LEVEL UP!");
    signalLevelUp->setStyleSheet("color:aqua");
    signalLevelUp->setFont(QFont("STCaiyun", 40, QFont::Bold));

    QPushButton *bulletBtn = new QPushButton("Level up bullet", this);
    QIcon bulletIcon(BULLET_PATH);
    bulletBtn->setIcon(bulletIcon);
    bulletBtn->setGeometry(400,700,250,100);
    bulletBtn->setFont(QFont("微软雅黑", 10, QFont::Bold));

    QPushButton *fireBtn = new QPushButton("Level up fire", this);
    QIcon fireIcon(FIRE_PATH3);
    fireBtn->setIcon(fireIcon);
    fireBtn->setGeometry(700,700,250,100);
    fireBtn->setFont(QFont("微软雅黑", 10, QFont::Bold));

    QPushButton *iceBtn = new QPushButton("Level up ice", this);
    QIcon iceIcon(ICE_PATH5);
    iceBtn->setIcon(iceIcon);
    iceBtn->setGeometry(1000,700,250,100);
    iceBtn->setFont(QFont("微软雅黑", 10, QFont::Bold));

    QPushButton *bloodBtn = new QPushButton("Add blood", this);
    bloodBtn->setGeometry(1300,700,250,100);
    bloodBtn->setFont(QFont("微软雅黑", 10, QFont::Bold));

    connect(this, &MainScene::levelUp, this, [=](){
        m_Timer.stop();
        bulletBtn->show();
        fireBtn->show();
        iceBtn->show();
        bloodBtn->show();
        signalLevelUp->show();
    });

    connect(bulletBtn, &QPushButton::clicked,this, [=](){
        m_game_data->bulletLevelUp();
        bulletBtn->close();
        fireBtn->close();
        iceBtn->close();
        bloodBtn->close();
        m_Timer.start();
        signalLevelUp->close();
    });

    connect(fireBtn, &QPushButton::clicked,this, [=](){
        m_game_data->fireLevelUp();
        bulletBtn->close();
        fireBtn->close();
        iceBtn->close();
        bloodBtn->close();
        m_Timer.start();
        signalLevelUp->close();
    });

    connect(iceBtn, &QPushButton::clicked,this, [=](){
        m_game_data->iceLevelUp();
        bulletBtn->close();
        fireBtn->close();
        iceBtn->close();
        bloodBtn->close();
        m_Timer.start();
        signalLevelUp->close();
    });

    connect(bloodBtn, &QPushButton::clicked, this, [=](){
        m_survivor.addBlood();
        bulletBtn->close();
        fireBtn->close();
        iceBtn->close();
        bloodBtn->close();
        m_Timer.start();
        signalLevelUp->close();
    });
}

void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY , m_map.m_map2);
    for(int i = 0; i < 5; i++)
        painter.drawPixmap(m_barrier[i].m_X, m_barrier[i].m_Y, m_barrier[i].m_Barrier);
    painter.drawPixmap(m_survivor.m_X, m_survivor.m_Y, m_survivor.m_Survivor);
    for(QVector<VampireBat>::iterator iter = m_bat_data.begin(); iter != m_bat_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Vampire);
    }
    for(QVector<VampireSkeleton>::iterator iter = m_ske_data.begin(); iter != m_ske_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Vampire);
    }
    for(QVector<VampireDemon>::iterator iter = m_demon_data.begin(); iter != m_demon_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Vampire);
    }
    for(QVector<VLightning>::iterator iter = m_lightning_data.begin(); iter != m_lightning_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Vampire);
    }
    for(QVector<WeaponBullet>::iterator iter = m_bullet_data.begin(); iter != m_bullet_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Weapon);
    }
    for(QVector<WeaponFire>::iterator iter = m_fire_data.begin(); iter != m_fire_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Weapon);
    }
    for(QVector<WeaponIce>::iterator iter = m_ice_data.begin(); iter != m_ice_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_Weapon);
    }
    for(QVector<ExpStone>::iterator iter = m_expstone_data.begin(); iter != m_expstone_data.end();iter++){
        painter.drawPixmap(iter->m_X, iter->m_Y, iter->m_ExpStone);
    }
    QBrush red_brush( QColor("#F20900") );//把刷子设置为红色
    painter.setBrush(red_brush);
    double rate = (double)m_survivor.HP/(double)m_survivor.bloodVolumn;
    painter.drawRect(m_survivor.m_X+20, m_survivor.m_Y+m_survivor.m_Rect.height(), rate*(m_survivor.m_Rect.width()-40), 6);
    for(QVector<VampireDemon>::iterator iter = m_demon_data.begin(); iter != m_demon_data.end();iter++){
        double rate = (double)iter->HP/(double)DEMON_BLOODVOLUMN;
        painter.drawRect(iter->m_X+50, iter->m_Y+iter->m_Rect.height(), rate*50, 6);
    }

    //显示当前时间
    painter.setPen("#F0FFFF");
    painter.setFont(QFont("Arial", 20,QFont::Bold));
    QString s = QString("%1").arg(pictureGlintCounter/100);
    painter.drawText(60, 80, "time:");
    painter.drawText(200,80, s);
    painter.drawText(60, 160, "level:");
    painter.drawText(200, 160, "1");
    painter.drawText(60, 240, "exp:");
    QString s1 = QString("%1").arg(m_survivor.EXP);
    painter.drawText(200, 240, s1);
    QBrush blue_brush( QColor("#000000") );
    painter.setBrush(blue_brush);

    //绘画此刻武器的level值
    QPixmap bulletPainter;
    bulletPainter.load(BULLET_PATH);
    painter.drawRect(60, GAME_HEIGHT-80, 45, 45);
    painter.drawPixmap(75, GAME_HEIGHT-65,bulletPainter);
    QString bulletLevel = QString("%1").arg(m_game_data->bulletLevel);
    painter.drawText(120, GAME_HEIGHT-40, bulletLevel);

    QPixmap firePainter;
    firePainter.load(FIRE_PATH3);
    painter.drawRect(180, GAME_HEIGHT-80, 45, 45);
    painter.drawPixmap(180, GAME_HEIGHT-75,firePainter);
    QString fireLevel = QString("%1").arg(m_game_data->fireLevel);
    painter.drawText(240, GAME_HEIGHT-40, fireLevel);

    QPixmap icePainter;
    icePainter.load(ICE_PATH0);
    painter.drawRect(300, GAME_HEIGHT-80, 45, 45);
    painter.drawPixmap(260, GAME_HEIGHT-120,icePainter);
    QString iceLevel = QString("%1").arg(m_game_data->iceLevel);
    painter.drawText(360, GAME_HEIGHT-40, iceLevel);

    //绘画此刻的金币值
    QPixmap coinPainter;
    coinPainter.load(COIN_PATH);
    painter.drawRect(420, GAME_HEIGHT-80, 45, 45);
    painter.drawPixmap(425, GAME_HEIGHT-75,coinPainter);
    QString coinNum = QString("%1").arg(m_game_data->coin);
    painter.drawText(480, GAME_HEIGHT-40, coinNum);
}

void MainScene::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    m_survivor.isRunning = true;
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(event->key());
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(4);

}

void MainScene::keyReleaseEvent(QKeyEvent *event){
    m_survivor.isRunning = false;
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(event->key());
    if(keys.isEmpty()) //容器空了，关闭定时器
        keyRespondTimer->stop();
}

void MainScene::slotTimeOut(){
    foreach (int key, keys) {
        switch (key) {
        case Qt::Key_W:
            if(m_survivor.m_Y < 50)    return;
            for(int i = 0; i < 5; i++)
                if(m_survivor.m_X < (m_barrier[i].m_X+m_barrier[i].m_Barrier.width()-40)
                    && m_survivor.m_X > m_barrier[i].m_X-m_survivor.m_Survivor.width()+60
                    && m_survivor.m_Y-10 < (m_barrier[i].m_Y+m_barrier[i].m_Barrier.height()-100)
                    && m_survivor.m_Y-10 > (m_barrier[i].m_Y-m_survivor.m_Survivor.height()+50))
                    return;
            m_survivor.moveUp();
            break;
        case Qt::Key_A:
            if(m_survivor.m_X < 50)    return;
            for(int i = 0; i < 5; i++)
                if(m_survivor.m_X-10 < (m_barrier[i].m_X+m_barrier[i].m_Barrier.width()-40)
                    && m_survivor.m_X-10 > m_barrier[i].m_X-m_survivor.m_Survivor.width()+60
                    && m_survivor.m_Y <(m_barrier[i].m_Y+m_barrier[i].m_Barrier.height()-100)
                    && m_survivor.m_Y > (m_barrier[i].m_Y-m_survivor.m_Survivor.height()+50))
                    return;
            m_survivor.moveLeft();
            break;
        case Qt::Key_S:
            if(m_survivor.m_Y > GAME_HEIGHT-180)    return;
            for(int i = 0; i < 5; i++)
            if(m_survivor.m_X < (m_barrier[i].m_X+m_barrier[i].m_Barrier.width()-40)
                && m_survivor.m_X > m_barrier[i].m_X-m_survivor.m_Survivor.width()+60
                && m_survivor.m_Y+10 < (m_barrier[i].m_Y+m_barrier[i].m_Barrier.height()-100)
                && m_survivor.m_Y+10 > (m_barrier[i].m_Y-m_survivor.m_Survivor.height()+50))
                    return;
            m_survivor.moveDown();
            break;
        case Qt::Key_D:
            if(m_survivor.m_X > GAME_WIDTH-120)    return;
            for(int i = 0; i < 5; i++)
            if(m_survivor.m_X+10 < (m_barrier[i].m_X+m_barrier[i].m_Barrier.width()-40)
                && m_survivor.m_X+10 > m_barrier[i].m_X-m_survivor.m_Survivor.width()+60
                && m_survivor.m_Y < (m_barrier[i].m_Y+m_barrier[i].m_Barrier.height()-100)
                && m_survivor.m_Y > (m_barrier[i].m_Y-m_survivor.m_Survivor.height()+50))
                return;
            m_survivor.moveRight();
            break;
        default:
            break;
        }
    }
}

void MainScene::succeedGame(){
    m_game_data->coin += 20;
    QPushButton *restartBtn = new QPushButton("RESTART", this);
    restartBtn->setGeometry(750,700,500,150);
    restartBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
    restartBtn->setStyleSheet("background-color:#DFDCDCDC;"
                              "border-radius: 50px;");
    restartBtn->raise();
    restartBtn->show();

    QLabel* signalSucceed = new QLabel(this);
    signalSucceed ->resize(500, 200);
    signalSucceed ->move(750, 400);
    signalSucceed ->setText("SUCCEED!");
    signalSucceed ->setStyleSheet("color:aqua");
    signalSucceed ->setFont(QFont("STCaiyun", 40, QFont::Bold));
    signalSucceed->show();

    connect(restartBtn, &QPushButton::clicked, [=](){
        restartBtn->close();
        signalSucceed->close();
        restartGame();
    });
}

void MainScene::loseGame(){
    QPushButton *restartBtn = new QPushButton("RESTART", this);
    restartBtn->setGeometry(750,700,500,150);
    restartBtn->setFont(QFont("微软雅黑", 18, QFont::Bold));
    restartBtn->setStyleSheet("background-color:#DFDCDCDC;"
                              "border-radius: 50px;");
    restartBtn->raise();
    restartBtn->show();

    QLabel* signalLose = new QLabel(this);
    signalLose ->resize(500, 200);
    signalLose ->move(750, 400);
    signalLose ->setText("FAILURE!");
    signalLose ->setStyleSheet("color:aqua");
    signalLose ->setFont(QFont("STCaiyun", 40, QFont::Bold));
    signalLose->show();

    connect(restartBtn, &QPushButton::clicked, [=](){
        restartBtn->close();
        signalLose->close();
        restartGame();
    });
}

void MainScene::restartGame(){
    m_survivor.initSurvivor();
    m_bat_data.clear();
    m_ske_data.clear();
    m_demon_data.clear();
    m_lightning_data.clear();

    //武器
    m_bullet_data.clear();
    m_fire_data.clear();
    m_ice_data.clear();

    pictureGlintCounter = 0;
    m_game_data->initGameData();
    m_Timer.start();
    qDebug() << m_game_data->coin;
}


