#include <list>
#include <Windows.h>
#include "resource.h"
#include "time.h"
using namespace std;

// 背景音乐
#define MAIN_BACK_MUSIC    "sounds/main_back.wav"
#define ONEGAME_BACK_MUSIC "sounds/back_mydream.wav"
#define TWOGAME_BACK_MUSIC "sounds/back_cool.wav"

// 游戏音效
#define START_GAME_SOUND   "sounds/start.wav"
#define WIN_GAME_SOUND     "sounds/win.wav"
#define LOST_GAME_SOUND    "sounds/lost.wav"
#define DRAW_GAME_SOUND    "sounds/draw.wav"
#define BLAST_SOUND        "sounds/blast.wav"
#define APPEAR_TOOL_SOUND  "sounds/appear.wav"
#define GET_TOOL_SOUND     "sounds/get.wav"
#define PUT_BUEBLE_SOUND   "sounds/put.wav"
#define PLAYER_DIE_SOUND   "sounds/die.wav"

// 定时器
#define TIMER_BEGIN					1
#define STOPSOUND_TIMER_ID          1 // 音效播完自动停止
#define BUBBLE_CHANGE_TIMER_ID      2 // 改变泡泡大小变化
#define GAME_TIME_TIMER_ID          3 // 游戏倒计时
#define STATUS_INFO_TIMER_ID        4 // 游戏状态文字移动
#define PLAYERSTART_TIMER_ID	    5 // 玩家开场动画
#define WIND_TIMER_ID               6 // 风车转动
#define PLAYER_MOVE_TIMER_ID        7 // 玩家移动
#define PLAYER_MOVE_SHOW_TIMER_ID   8 // 玩家移动show
#define PROPERTY_CHANGR_TIMER_ID    9 // 道具变化
#define PROPERTY_BOOM_TIMER_ID		10 // 泡泡爆炸
#define PLAYERSTART_DIE_ID			11 // 玩家死亡
#define TIMER_END					11

// 人物属性
#define _DEF_BUBBLE_POWER_MAX       4  // 泡泡威力最大值
#define _DEF_BUBBLE_NUM_MAX         5  // 泡泡最大放置个数
#define _DEF_PLAYER_SPEED_TIMER     40 // 玩家移动最大定时器时间

// 道具数量
#define EBNUMBER   5    // 水泡赠加水泡数量
#define EWNUMBER   5    // 能量水赠加爆炸范围
#define RSNUMBER   5    // 旱冰鞋增加速度
#define RHNUMBER   1    // 红魔头速度增到最大
#define PBNUMBER   1    // 大力丸爆炸范围最大