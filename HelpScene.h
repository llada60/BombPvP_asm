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

