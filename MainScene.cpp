#include "MainScene.h"
#pragma comment(lib,"Msimg32.lib")


CMainScene::CMainScene()
{
	m_bitmap_mainBack = NULL;
	m_bitmap_twoGame = NULL;
	m_bitmap_gameHelp = NULL;
	m_bitmap_quitGame = NULL;
	m_bitmap_twoGame_in = NULL;
	m_bitmap_gameHelp_in = NULL;
	m_bitmap_quitGame_in = NULL;

	m_seclectNum = NO;
}


CMainScene::~CMainScene()
{
	DeleteObject(m_bitmap_mainBack);
	DeleteObject(m_bitmap_twoGame);
	DeleteObject(m_bitmap_gameHelp);
	DeleteObject(m_bitmap_quitGame);
	DeleteObject(m_bitmap_twoGame_in);
	DeleteObject(m_bitmap_gameHelp_in);
	DeleteObject(m_bitmap_quitGame_in);
	m_bitmap_mainBack = NULL;
	m_bitmap_twoGame = NULL;
	m_bitmap_gameHelp = NULL;
	m_bitmap_quitGame = NULL;
	m_bitmap_twoGame_in = NULL;
	m_bitmap_gameHelp_in = NULL;
	m_bitmap_quitGame_in = NULL;
}

void CMainScene::MainSceneInit(HINSTANCE hIns)
{
	m_bitmap_mainBack = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAIN_BACK));
	m_bitmap_twoGame = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TWO_GAME));
	m_bitmap_gameHelp = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_HELP));
	m_bitmap_quitGame = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_QUIT));
	m_bitmap_twoGame_in = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TWO_GAME_SELECT));
	m_bitmap_gameHelp_in = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_HELP_SELECT));
	m_bitmap_quitGame_in = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_QUIT_SELECT));
}

void CMainScene::MainSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_mainBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);

	if (m_seclectNum == TWO_GAME)
	{
		SelectObject(hdcMem,m_bitmap_twoGame_in);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_twoGame);
	}
	TransparentBlt(hdc,250,200,197,61,hdcMem,0,0,197,61,RGB(128,128,128));

	if (m_seclectNum == HELP_GAME)
	{
		SelectObject(hdcMem,m_bitmap_gameHelp_in);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_gameHelp);
	}
	TransparentBlt(hdc,350,300,197,61,hdcMem,0,0,197,61,RGB(128,128,128));

	if (m_seclectNum == QUIT_GAME)
	{
		SelectObject(hdcMem,m_bitmap_quitGame_in);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_quitGame);
	}
	TransparentBlt(hdc,450,400,197,61,hdcMem,0,0,197,61,RGB(128,128,128));

	DeleteDC(hdcMem);
}

void CMainScene::MouseMove(POINT point)
{
	if (point.x > 250 && point.x < 447 && point.y > 200 && point.y < 261)
	{
		m_seclectNum = TWO_GAME;
	}
	else if (point.x > 350 && point.x < 547 && point.y > 300 && point.y < 361)
	{
		m_seclectNum = HELP_GAME;
	}
	else if (point.x > 450 && point.x < 647 && point.y > 400 && point.y < 461)
	{
		m_seclectNum = QUIT_GAME;
	}
	else
	{
		m_seclectNum = NO;
	}
}
