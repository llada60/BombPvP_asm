/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CHelpScene.h
 *  简要描述: 帮助场景类,显示游戏说明信息
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
#ifndef CHELPSCENE_H_
#define CHELPSCENE_H_

#include "Sys.h"

class CHelpScene
{
public:
	CHelpScene();
	~CHelpScene();
public:
	void HelpSceneInit(HINSTANCE hIns);
	void HelpSceneShow(HDC hdc);

	// 根据鼠标位置 修改 m_isSelect 标记是否鼠标悬浮返回框
	void MouseMove(POINT point);

	/* 标记鼠标是否悬浮于返回选择框
	** true: 鼠标在返回框上
	** false: 鼠标未在返回框上
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_help;
	HBITMAP m_bitmap_return;
	HBITMAP m_bitmap_return_select;
};

#endif // !CHELPSCENE_H_

