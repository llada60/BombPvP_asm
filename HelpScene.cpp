#include "HelpScene.h"


CHelpScene::CHelpScene()
{
	m_bitmap_help = NULL;
	m_bitmap_return = NULL;
	m_bitmap_return_select = NULL;

	m_isSelect = false;
}


CHelpScene::~CHelpScene()
{
	DeleteObject(m_bitmap_help);
	DeleteObject(m_bitmap_return);
	DeleteObject(m_bitmap_return_select);
	m_bitmap_help = NULL;
	m_bitmap_return = NULL;
	m_bitmap_return_select = NULL;
}

void CHelpScene::HelpSceneInit(HINSTANCE hIns)
{
	m_bitmap_help = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_HELP_BACK));
	m_bitmap_return = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_RETURN));
	m_bitmap_return_select = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_RETURN_SELECT));
}

void CHelpScene::HelpSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_help);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
	if (m_isSelect)
	{
		SelectObject(hdcMem,m_bitmap_return_select);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_return);
	}
	
	BitBlt(hdc,0,562,80,38,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);
}

void CHelpScene::MouseMove(POINT point)
{
	if (point.x > 0 && point.x < 80 && point.y > 562 && point.y < 600)
	{
		m_isSelect = true;
	}
	else
	{
		m_isSelect = false;
	}
}
