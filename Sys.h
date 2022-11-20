#include <list>
#include <Windows.h>
#include "resource.h"
#include "time.h"
using namespace std;

// ��������
#define MAIN_BACK_MUSIC    "sounds/main_back.wav"
#define ONEGAME_BACK_MUSIC "sounds/back_mydream.wav"
#define TWOGAME_BACK_MUSIC "sounds/back_cool.wav"

// ��Ϸ��Ч
#define START_GAME_SOUND   "sounds/start.wav"
#define WIN_GAME_SOUND     "sounds/win.wav"
#define LOST_GAME_SOUND    "sounds/lost.wav"
#define DRAW_GAME_SOUND    "sounds/draw.wav"
#define BLAST_SOUND        "sounds/blast.wav"
#define APPEAR_TOOL_SOUND  "sounds/appear.wav"
#define GET_TOOL_SOUND     "sounds/get.wav"
#define PUT_BUEBLE_SOUND   "sounds/put.wav"
#define PLAYER_DIE_SOUND   "sounds/die.wav"

// ��ʱ��
#define TIMER_BEGIN					1
#define STOPSOUND_TIMER_ID          1 // ��Ч�����Զ�ֹͣ
#define BUBBLE_CHANGE_TIMER_ID      2 // �ı����ݴ�С�仯
#define GAME_TIME_TIMER_ID          3 // ��Ϸ����ʱ
#define STATUS_INFO_TIMER_ID        4 // ��Ϸ״̬�����ƶ�
#define PLAYERSTART_TIMER_ID	    5 // ��ҿ�������
#define WIND_TIMER_ID               6 // �糵ת��
#define PLAYER_MOVE_TIMER_ID        7 // ����ƶ�
#define PLAYER_MOVE_SHOW_TIMER_ID   8 // ����ƶ�show
#define PROPERTY_CHANGR_TIMER_ID    9 // ���߱仯
#define PROPERTY_BOOM_TIMER_ID		10 // ���ݱ�ը
#define PLAYERSTART_DIE_ID			11 // �������
#define TIMER_END					11

// ��������
#define _DEF_BUBBLE_POWER_MAX       4  // �����������ֵ
#define _DEF_BUBBLE_NUM_MAX         5  // ���������ø���
#define _DEF_PLAYER_SPEED_TIMER     40 // ����ƶ����ʱ��ʱ��

// ��������
#define EBNUMBER   5    // ˮ������ˮ������
#define EWNUMBER   5    // ����ˮ���ӱ�ը��Χ
#define RSNUMBER   5    // ����Ь�����ٶ�
#define RHNUMBER   1    // ��ħͷ�ٶ��������
#define PBNUMBER   1    // �����豬ը��Χ���