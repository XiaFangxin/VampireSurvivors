#ifndef CONFIG_H
#define CONFIG_H
#define GAME_RES_PATH  "./rs.rcc" //rcc文件路径
#define GAME_ICON  ":/res/idle_1.png"

/**********  游戏配置数据 **********/
#define GAME_WIDTH  1930  //宽度
#define GAME_HEIGHT 1460 //高度1460
#define GAME_TITLE "VampireSurvivor v1.0" //标题

/**********  地图配置数据 **********/
#define MAP_PATH  ":/res/map2.png" //地图图片路径
#define MAP_SCROLL_SPEED 0  //地图滚动速度

#define GAME_RATE 10  //刷新间隔，帧率 单位毫秒
#define GAME_TIME_DURATION 60//second

/**********  金币配置数据 **********/
#define COIN_PATH ":/res/coin.png"
#define REVIVAL_PRICE 10

/**********  幸存者配置数据 **********/
#define SURVIVOR_PATH0 ":/res/idle_1.png"
#define SURVIVOR_PATH1 ":/res/idle_2.png"
#define SURVIVOR_PATH2 ":/res/idle_3.png"
#define SURVIVOR_PATH3 ":/res/idle_4.png"
#define SURVIVOR_PATH4 ":/res/idle_5.png"
#define SURVIVOR_PATH5 ":/res/idle_6.png"
#define SURVIVOR_RUN_PATH0 ":/res/run_1.png"
#define SURVIVOR_RUN_PATH1 ":/res/run_2.png"
#define SURVIVOR_RUN_PATH2 ":/res/run_3.png"
#define SURVIVOR_RUN_PATH3 ":/res/run_4.png"
#define SURVIVOR_RUN_PATH4 ":/res/run_5.png"
#define SURVIVOR_RUN_PATH5 ":/res/run_6.png"
#define SURVIVOR_RUN_PATH6 ":/res/run_7.png"
#define SURVIVOR_RUN_PATH7 ":/res/run_8.png"
#define SURVIVOR_ATTACKED_PATH ":/res/attacked.png"
#define SURVIVOR_SPEED 1 //幸存者移动速度

/**********  障碍物配置数据 **********/
#define BARRIER_PATH ":/res/stone.png"

/********** 吸血鬼Bat配置数据 **********/
#define BAT_PATH0 ":/res/bat_0.png"
#define BAT_PATH1 ":/res/bat_1.png"
#define BAT_PATH2 ":/res/bat_2.png"
#define BAT_PATH3 ":/res/bat_3.png"
#define BAT_PATH4 ":/res/bat_4.png"
#define BAT_PATH5 ":/res/bat_5.png"
#define BAT_PATH6 ":/res/bat_6.png"
#define BAT_PATH7 ":/res/bat_7.png"
#define BAT_PATH8 ":/res/bat_8.png"
#define BAT_PATH9 ":/res/bat_9.png"
#define BAT_PATH10 ":/res/bat_10.png"
#define BAT_SPEED 1
#define BAT_INTERVAL 500

/********** 吸血鬼Skeleton配置数据 **********/
#define SKE_PATH0 ":/res/ske_0.png"
#define SKE_PATH1 ":/res/ske_1.png"
#define SKE_PATH2 ":/res/ske_2.png"
#define SKE_PATH3 ":/res/ske_3.png"
#define SKE_PATH4 ":/res/ske_4.png"
#define SKE_PATH5 ":/res/ske_5.png"
#define SKE_PATH6 ":/res/ske_6.png"
#define SKE_PATH7 ":/res/ske_7.png"
#define SKE_PATH8 ":/res/ske_8.png"
#define SKE_PATH9 ":/res/ske_9.png"
#define SKE_PATH10 ":/res/ske_10.png"
#define SKE_PATH11 ":/res/ske_11.png"
#define SKE_PATH12 ":/res/ske_12.png"
#define SKE_PATH13 ":/res/ske_13.png"
#define SKE_PATH14 ":/res/ske_14.png"
#define SKE_RUN_PATH0 ":/res/ske_run0.png"
#define SKE_RUN_PATH1 ":/res/ske_run1.png"
#define SKE_RUN_PATH2 ":/res/ske_run2.png"
#define SKE_RUN_PATH3 ":/res/ske_run3.png"
#define SKE_RUN_PATH4 ":/res/ske_run4.png"
#define SKE_RUN_PATH5 ":/res/ske_run5.png"
#define SKE_RUN_PATH6 ":/res/ske_run6.png"
#define SKE_RUN_PATH7 ":/res/ske_run7.png"
#define SKE_RUN_PATH8 ":/res/ske_run8.png"
#define SKE_RUN_PATH9 ":/res/ske_run9.png"
#define SKE_RUN_PATH10 ":/res/ske_run10.png"
#define SKE_RUN_PATH11 ":/res/ske_run11.png"
#define SKE_SPEED 20
#define SKE_INTERVAL 500

/********** 吸血鬼Demon配置数据 **********/
#define DEMON_PATH ":/res/FlameDemon.png"
#define LIGHTNING_PATH0 ":/res/lightning_0.png"
#define LIGHTNING_PATH1 ":/res/lightning_1.png"
#define LIGHTNING_PATH2 ":/res/lightning_2.png"
#define LIGHTNING_PATH3 ":/res/lightning_3.png"
#define LIGHTNING_PATH4 ":/res/lightning_4.png"
#define LIGHTNING_PATH5 ":/res/lightning_5.png"
#define LIGHTNING_PATH6 ":/res/lightning_6.png"
#define LIGHTNING_PATH7 ":/res/lightning_7.png"
#define DEMON_SPEED 20
#define DEMON_INTERVAL 2000
#define DEMON_BLOODVOLUMN 200
#define LIGHTNING_SPEED 50
#define LIGHTNING_INTERVAL 20
#define LIGHTNING_DURATION 300

enum Direction{
    LEFT,RIGHT,UP,DOWN
};

/********** 武器配置数据 **********/
#define WEAPON_SPEED 1
#define WEAPON_INTERVAL 70
#define WEAPON_DURATION 500

/******** 武器Bullet配置数据 ********/
#define BULLET_PATH ":/res/bullet.png"

/******** 武器Fire配置数据 ********/
#define FIRE_PATH0 ":/res/fire_0.png"
#define FIRE_PATH1 ":/res/fire_1.png"
#define FIRE_PATH2 ":/res/fire_2.png"
#define FIRE_PATH3 ":/res/fire_3.png"
#define FIRE_PATH4 ":/res/fire_4.png"
#define FIRE_PATH5 ":/res/fire_5.png"
#define FIRE_PATH6 ":/res/fire_6.png"
#define FIRE_PATH7 ":/res/fire_7.png"
#define FIRE_PATH8 ":/res/fire_8.png"
#define FIRE_PATH9 ":/res/fire_9.png"
#define FIRE_PATH10 ":/res/fire_10.png"
#define FIRE_PATH11 ":/res/fire_11.png"
#define FIRE_PATH12 ":/res/fire_12.png"
#define FIRE_PATH13 ":/res/fire_13.png"
#define FIRE_PATH14 ":/res/fire_14.png"
#define FIRE_PATH15 ":/res/fire_15.png"
#define FIRE_PATH16 ":/res/fire_16.png"

/******** 武器Ice配置数据 ********/
#define ICE_PATH0 ":/res/ice_0.png"
#define ICE_PATH1 ":/res/ice_1.png"
#define ICE_PATH2 ":/res/ice_2.png"
#define ICE_PATH3 ":/res/ice_3.png"
#define ICE_PATH4 ":/res/ice_4.png"
#define ICE_PATH5 ":/res/ice_5.png"
#define ICE_PATH6 ":/res/ice_6.png"
#define ICE_PATH7 ":/res/ice_7.png"
#define ICE_PATH8 ":/res/ice_8.png"
#define ICE_PATH9 ":/res/ice_9.png"


/********** 经验石配置数据 **********/
#define EXPSTONE_PATH ":/res/expStone.png"

#endif // CONFIG_H
