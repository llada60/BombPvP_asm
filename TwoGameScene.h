/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CTwoGameScene.h
 *  简要描述: 双人游戏场景类 双人游戏操作交互由该类控制
 *
 *  作者: 刘新成
 *  创建日期: 2017年6月3日
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 *  当前版本: 1.0
 ******************************************************************/ 
#ifndef CTWOGAMESCENE_H_
#define CTWOGAMESCENE_H_

#include "Sys.h"
#include "GameMap.h"
#include "PlaySound.h"
#include "Bubble.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "GameProps.h"

enum GameStatus { NO_SHOW, START, PLAYER_ONE_WIN, PLAYER_TWO_WIN, DRAW };

class CTwoGameScene
{
public:
	CTwoGameScene();
	~CTwoGameScene();

	// 地图
	CGameMap gameMap;
	// 音效
	CPlaySound playSound;
	// 玩家
	CPlayerOne playerOne;
	CPlayerTwo playerTwo;
	//道具
	CGameProps prop;
public:
	void TwoGameSceneInit(HINSTANCE hIns, HWND hWnd);
	void TwoGameSceneShow(HDC hdc);
	void MouseMove(POINT point);
	void OnLButtonDown(HINSTANCE hIns,POINT point);
	void OnKeyDown(WPARAM nKey);
	void OnKeyUp(WPARAM nKey);
	void OnTwoGameRun(WPARAM nTimerID);

	void ChangeBubbleShowID();
	void ChangeBoomShowID();
	void AllBubbleShow(HDC hdc);
	void AllBoomShow(HDC hdc);

	void ShowTime(HDC hdc);         // 倒计时显示
	void ShowGameStatus(HDC hdc);   // 游戏状态文字提示

	void ChangePlayerStartShowID();
	void ChangePropShowID();

	void SetFx(list<CBubble*>::iterator &ite_Bubble, int i, int j); //设置四个方向数值
	bool IsKillPlayerOne(list<CBubble*>::iterator &ite_Bubble, int i, int j);
	bool IsKillPlayerTwo(list<CBubble*>::iterator &ite_Bubble, int i, int j);
	bool IsButtleBoom(list<CBubble*>::iterator &ite_JBubble, list<CBubble*>::iterator &ite_Bubble);

	void GameOver();
public: 
	/* 标记鼠标是否悬浮于退出选择框
	** true: 鼠标在退出框上
	** false: 鼠标未在退出框上
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_gameBack;      // 游戏背景位图
	HBITMAP m_bitmap_road;          // 游戏背景马路
	HBITMAP m_bitmap_quit;          // 退出选项位图
	HBITMAP m_bitmap_quit_select;   // 退出选项选中位图
	HBITMAP m_bitmap_timeNum;       // 时间数字位图
	HBITMAP m_bitmap_statusInfo;    // 游戏状态信息提示位图：开始，胜利，平局，失败
	HBITMAP m_bitmap_win_word;      // 提示第几玩家胜利文字位图

	HWND m_twoGameWnd;              // 窗口句柄
	HINSTANCE m_twoGameHIns;
	int m_gameTime;                 // 倒计时时间 默认五分钟（300s）
	int m_statusInfo_y;             // 游戏状态文字位置

	list<CBubble*> m_lstBubble;     // 泡泡链表
	list<CBubble*> m_lstBoom;		// 爆炸泡泡链表

	GameStatus m_gameStatus;        // 枚举类型：记录显示游戏状态文字 开始 胜利 平局 失败
};

#endif // !CTWOGAMESCENE_H_

