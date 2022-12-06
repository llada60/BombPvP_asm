#ifndef CBNBAPP_H_
#define CBNBAPP_H_

#include "Sys.h"
#include "CGameCtrl.h"
#include "MainScene.h"
#include "TwoGameScene.h"
#include "HelpScene.h"
#include "PlayMusic.h"

/*
** 场景标志：主场景、单人游戏场景、双人游戏场景、帮助场景
*/
enum SeclectScene { MAIN_SCENE,  TWO_GAME_SCENE, HELP_GAME_SCENE };

class CBnbApp : public CGameCtrl
{
public:
	CBnbApp();
	~CBnbApp();
public:
	DECLARE()

	// 加载 三个场景类： 主场景、 双人游戏场景、 帮助场景
	CMainScene* mainScene;
	CTwoGameScene* twoGameScene;
	CHelpScene* helpScene;
	CPlayMusic* playMusic;
public:
	// 重写父类函数
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
	virtual void OnKeyUp(WPARAM nKey);
	virtual void OnLButtonDown(POINT point);
	virtual void OnLButtonUp(POINT point);
	virtual void OnMouseMove(POINT point);
public:
	/*
	** 根据鼠标点击主场景的不同选项，切换相应场景（BnbApp类中响应鼠标左键抬起函数 OnLButtonUp 调用）
	*/
	void ChangeScene();

	/*
	** 播放与暂停背景音乐函数：按键F8及切换不同场景调用
	*/
	void PlayBackMusic();

private:
	// 场景标记: 判断当前处于哪个场景，不同场景不同操作 默认主场景（CMainScene mainScene）
	SeclectScene m_seclectScene;

	// 标记位： 当F8停止音乐时，切换场景后也不会播放音乐，直至F8打开音乐
	bool isKey_stopMusic;
};

#endif // !CBNBAPP_H_

