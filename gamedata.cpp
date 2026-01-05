#include "gamedata.h"

GameData::GameData()
{
    coin = 20;
    revivalNum = 0;
    initGameData();
}

void GameData::initGameData(){
    bat_speed = 1;
    bat_interval = 500;

    ske_speed = 20;
    ske_interval = 500;

    demon_speed = 20;
    demon_interval = 4000;
    demon_bloodvolumn = 200;
    lightning_speed = 50;
    lightning_interval = 20;
    lightning_duration= 300;

    bullet_speed = 1;
    bullet_interval = 100;//
    bullet_duration = 400;//

    fire_speed = 1;
    fire_interval = 1200;//
    fire_duration = 500;//

    ice_speed = 1;
    ice_num = 8;//
    ice_interval = 1200;//
    ice_duration = 500;

    bulletLevel = 1;
    fireLevel = 1;
    iceLevel = 1;

    haveRevivaled = false;
}

void GameData::bulletLevelUp(){
    bulletLevel++;
    switch(bulletLevel%2){
    case(0):
        bullet_interval *= 0.9;break;
    case(1):
        bullet_duration += 100;
    }
}

void GameData::fireLevelUp(){
    fireLevel++;
    switch(fireLevel%2){
    case(0):
        if(fire_interval >= 700)
            fire_interval -= 100;break;
    case(1):
        fire_duration += 100;break;
    }
}

void GameData::iceLevelUp(){
    iceLevel++;
    switch(iceLevel%2){
    case(0):
        ice_num += 4;break;
    case(1):
        if(ice_interval >= 700)
            ice_interval -= 100; break;
    }
}

void GameData::read(const QJsonObject &json){
    if(json.contains("coin") && json["coin"].isDouble())
        mCoin = json["coin"].toInt();
}

void GameData::write(QJsonObject &json) const{
    json["coin"] = mCoin;
}
