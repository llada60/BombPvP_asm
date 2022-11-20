#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "Sys.h"
#include "GameMap.h"
#include "Bubble.h"
#include "PlaySound.h"
#include "GameProps.h"
enum Player_Status {BEGIN, MOVE, DIE};
enum Direction { UP, DOWN, LEFT, RIGHT };

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void PlayerInit(HINSTANCE hIns) = 0; // 玩家初始化
	virtual void PlayerShow(HDC hdc) = 0;        // 玩家出场动画
	virtual void PlayerMove(int FX,CGameMap &gameMap,CGameProps &gameProp,CPlaySound &playSound) = 0;         // 玩家移动
	virtual void CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y) = 0;
	virtual bool WhetherProp(CGameProps &gameprop)=0;     //判断位置是否有道具
public:
	HBITMAP m_hBmpPlayerStart;                   // 开始动画位图
	HBITMAP m_hBmpPlayerMove;                    // 移动动画位图
	HBITMAP m_hBmpPlayerDie;                     // 死亡动画位图
	HBITMAP m_hBmpPlayerShadow;                  // 人物阴影位图
	int m_Start_nShowID;                         // 人物开始动画切换位图
	int m_player_x;                              // 人物位置 x
	int m_player_y;                              // 人物位置 y
	int m_Move_ShowId;                           // 人物移动 改变图片标记
	bool m_bMoveFlag;                            // 标记哪个人物移动
	int m_DieShowID;                             // 人物死亡动画标记
	int m_speed_timer;                           // 人物通过道具改变移动速度
	int m_bubbleNum;                             // 泡泡个数
	int m_bubblePower;                           // 泡泡威力
	// 记录玩家状态 切换不同位图动画
	Player_Status m_player_status;
	// 记录玩家移动方向
	Direction m_direction;
};

#endif // !CPLAYER_H_
