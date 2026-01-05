#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QJsonObject>

class GameData
{
public:
    int bat_speed;
    int bat_interval;

    int ske_speed;
    int ske_interval;

    int demon_speed;
    int demon_interval;
    int demon_bloodvolumn;
    int lightning_speed;
    int lightning_interval;
    int lightning_duration;

    int bullet_speed;
    int bullet_interval;
    int bullet_duration;

    int fire_speed;
    int fire_interval;
    int fire_duration;

    int ice_speed;
    int ice_num;
    int ice_interval;
    int ice_duration;

    int bulletLevel;
    int fireLevel;
    int iceLevel;

    int coin;
    int revivalNum;
    bool haveRevivaled;

private:
    int mCoin;

public:
    GameData();
    void initGameData();
    void bulletLevelUp();
    void fireLevelUp();
    void iceLevelUp();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

};

#endif // GAMEDATA_H
