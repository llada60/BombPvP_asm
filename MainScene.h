/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CMainScene.h
 *  简要描述: 主场景类，游戏启动默认场景
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
#ifndef CMAINSCENE_H_
#define CMAINSCENE_H_

#include "Sys.h"

/*
** 鼠标悬浮于主页选项：无选中、悬浮于单人游戏、悬浮于双人游戏、悬浮于帮助、悬浮于退出
*/
enum SeclectNum { NO, TWO_GAME, HELP_GAME, QUIT_GAME };

class CMainScene
{
public:
	CMainScene();
	~CMainScene();
public:
	void MainSceneInit(HINSTANCE hIns);
	void MainSceneShow(HDC hdc);

	// 根据鼠标位置 将 m_seclectNum 修改成相应值 标记处于哪个选项
	void MouseMove(POINT point);

	// 标记鼠标悬浮于哪个选项
	SeclectNum m_seclectNum;
private:
	HBITMAP m_bitmap_mainBack;
	HBITMAP m_bitmap_twoGame;
	HBITMAP m_bitmap_gameHelp;
	HBITMAP m_bitmap_quitGame;
	HBITMAP m_bitmap_twoGame_in;
	HBITMAP m_bitmap_gameHelp_in;
	HBITMAP m_bitmap_quitGame_in;
};

#endif // !CMAINSCENE_H_

