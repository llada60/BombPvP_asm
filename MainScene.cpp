#include "MainScene.h"
#pragma comment(lib,"Msimg32.lib")


CMainScene::CMainScene()
{
	_asm {
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 4], 0 // m_bitmap_mainBack = NULL;
		mov         dword ptr[eax + 8], 0 // m_bitmap_twoGame = NULL;
		mov         dword ptr[eax + 0Ch], 0 // m_bitmap_gameHelp = NULL;
		mov         dword ptr[eax + 10h], 0 // m_bitmap_quitGame = NULL;
		mov         dword ptr[eax + 14h], 0 // m_bitmap_twoGame_in = NULL;
		mov         dword ptr[eax + 18h], 0 // m_bitmap_gameHelp_in = NULL;
		mov         dword ptr[eax + 1Ch], 0 // m_bitmap_quitGame_in = NULL;
		mov         dword ptr[eax], 0 // m_seclectNum = NO;
	}
}


CMainScene::~CMainScene()
{
	_asm {
		// DeleteObject(m_bitmap_mainBack);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_mainBack]
		push        ecx
		call        DeleteObject
		// DeleteObject(m_bitmap_twoGame);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_twoGame]
		push        ecx
		call        DeleteObject
		// DeleteObject(m_bitmap_gameHelp);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_gameHelp]
		push        ecx
		call        DeleteObject
		//DeleteObject(m_bitmap_quitGame);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_quitGame]
		push        ecx
		call        DeleteObject
		//DeleteObject(m_bitmap_twoGame_in);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_twoGame_in]
		push        ecx
		call        DeleteObject
		//DeleteObject(m_bitmap_gameHelp_in);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_gameHelp_in]
		push        ecx
		call        DeleteObject
		//DeleteObject(m_bitmap_quitGame_in);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_quitGame_in]
		push        ecx
		call        DeleteObject
		//m_bitmap_mainBack = NULL;
		//m_bitmap_twoGame = NULL;
		//m_bitmap_gameHelp = NULL;
		//m_bitmap_quitGame = NULL;
		//m_bitmap_twoGame_in = NULL;
		//m_bitmap_gameHelp_in = NULL;
		//m_bitmap_quitGame_in = NULL;
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 4], 0
		mov         dword ptr[eax + 8], 0
		mov         dword ptr[eax + 0Ch], 0
		mov         dword ptr[eax + 10h], 0
		mov         dword ptr[eax + 14h], 0
		mov         dword ptr[eax + 18h], 0
		mov         dword ptr[eax + 1Ch], 0
	}
}

void CMainScene::MainSceneInit(HINSTANCE hIns)
{
	_asm {
		// m_bitmap_mainBack = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_MAIN_BACK));
		push        IDB_MAIN_BACK
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 4], eax
		// m_bitmap_twoGame = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TWO_GAME));
		push        IDB_TWO_GAME
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 8], eax
		// m_bitmap_gameHelp = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_HELP));
		push        IDB_HELP
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 0Ch], eax
		// m_bitmap_quitGame = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT));
		push        IDB_QUIT
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 10h], eax
		// m_bitmap_twoGame_in = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_TWO_GAME_SELECT));
		push        IDB_TWO_GAME_SELECT
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 14h], eax
		// m_bitmap_gameHelp_in = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_HELP_SELECT));
		push        IDB_HELP_SELECT
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 18h], eax
		// m_bitmap_quitGame_in = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_SELECT));
		push        IDB_QUIT_SELECT
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 1Ch], eax
	}
}

void CMainScene::MainSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	_asm {
		// SelectObject(hdcMem,m_bitmap_mainBack);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 4] // m_bitmap_mainBack
		push        ecx
		mov         edx, dword ptr[hdcMem]
		push        edx
		call        SelectObject
		// BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
		push        0CC0020h
		push        0
		push        0
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        600
		push        800
		push        0
		push        0
		mov         ecx, dword ptr[hdc]
		push        ecx
		call        BitBlt
		//if (m_seclectNum == TWO_GAME)
		//	SelectObject(hdcMem, m_bitmap_twoGame_in);
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax], TWO_GAME
		jne			TwoGameNeq
		mov         ecx, dword ptr[eax + 14h] // m_bitmap_twoGame_in
		push        ecx
		mov         edx, dword ptr[hdcMem]
		push        edx
		call        SelectObject
		jmp			Trans
		TwoGameNeq :
		//else
		//	SelectObject(hdcMem, m_bitmap_twoGame);
		mov         ecx, dword ptr[eax + 8] // m_bitmap_twoGam
			push        ecx
			mov         edx, dword ptr[hdcMem]
			push        edx
			call        SelectObject
			Trans :
		// TransparentBlt(hdc, 250, 200, 197, 61, hdcMem, 0, 0, 197, 61, RGB(128, 128, 128));
		push        808080h
			push        61
			push        197
			push        0
			push        0
			mov         eax, dword ptr[hdcMem]
			push        eax
			push        61
			push        197
			push        200
			push        250
			mov         ecx, dword ptr[hdc]
			push        ecx
			call        TransparentBlt
			// if (m_seclectNum == HELP_GAME)
			// SelectObject(hdcMem,m_bitmap_gameHelp_in);
			mov         eax, dword ptr[this]
			cmp         dword ptr[eax], HELP_GAME
			jne			HelpGameNeq
			mov         ecx, dword ptr[eax + 18h] // m_bitmap_gameHelp_in
			push        ecx
			mov         edx, dword ptr[hdcMem]
			push        edx
			call        SelectObject
			jmp			Trans2
			HelpGameNeq :
		//else
		//	SelectObject(hdcMem, m_bitmap_gameHelp);
		mov         ecx, dword ptr[eax + 0Ch] // m_bitmap_gameHelp
			push        ecx
			mov         edx, dword ptr[hdcMem]
			push        edx
			call        SelectObject
			Trans2 :
		// TransparentBlt(hdc,350,300,197,61,hdcMem,0,0,197,61,RGB(128,128,128));
		push        808080h
			push        61
			push        197
			push        0
			push        0
			mov         eax, dword ptr[hdcMem]
			push        eax
			push        61
			push        197
			push        300
			push        350
			mov         ecx, dword ptr[hdc]
			push        ecx
			call        TransparentBlt
			// if (m_seclectNum == QUIT_GAME)
			//	 SelectObject(hdcMem, m_bitmap_quitGame_in);
			mov         eax, dword ptr[this]
			cmp         dword ptr[eax], QUIT_GAME
			jne			QuitGameNeq
			mov         ecx, dword ptr[eax + 1Ch] // m_bitmap_quitGame_in
			push        ecx
			mov         edx, dword ptr[hdcMem]
			push        edx
			call        SelectObject
			jmp			Trans3
			QuitGameNeq :
		//else
		//	SelectObject(hdcMem, m_bitmap_quitGame);
		mov         ecx, dword ptr[eax + 10h] // m_bitmap_quitGame
			push        ecx
			mov         edx, dword ptr[hdcMem]
			push        edx
			call        SelectObject
			Trans3 :
		//TransparentBlt(hdc,450,400,197,61,hdcMem,0,0,197,61,RGB(128,128,128));
		push        808080h
			push        61
			push        197
			push        0
			push        0
			mov         eax, dword ptr[hdcMem]
			push        eax
			push        61
			push        197
			push        400
			push        450
			mov         ecx, dword ptr[hdc]
			push        ecx
			call        TransparentBlt
			// DeleteDC(hdcMem);
			mov         eax, dword ptr[hdcMem]
			push        eax
			call        DeleteDC
	}
}

void CMainScene::MouseMove(POINT point)
{
	_asm {
		//if (point.x > 250 && point.x < 447 && point.y > 200 && point.y < 261)
		//	m_seclectNum = TWO_GAME;
		cmp         dword ptr[point.x], 250
		jle         If2
		cmp         dword ptr[point.x], 447
		jge         If2
		cmp         dword ptr[point.y], 200
		jle         If2
		cmp         dword ptr[point.y], 261
		jge         If2
		mov         eax, dword ptr[this]
		mov         dword ptr[eax], TWO_GAME
		jmp			Done
		If2 :
		cmp         dword ptr[point.x], 350
			jle         If3
			cmp         dword ptr[point.x], 547
			jge         If3
			cmp         dword ptr[point.y], 300
			jle         If3
			cmp         dword ptr[point.y], 361
			jge         If3
			mov         eax, dword ptr[this]
			mov         dword ptr[eax], HELP_GAME
			jmp			Done
			If3 :
		cmp         dword ptr[point.x], 450
			jle         If4
			cmp         dword ptr[point.x], 647
			jge         If4
			cmp         dword ptr[point.y], 400
			jle         If4
			cmp         dword ptr[point.y], 461
			jge         If4
			mov         eax, dword ptr[this]
			mov         dword ptr[eax], QUIT_GAME
			jmp			Done
			If4 :
		mov         eax, dword ptr[this]
			mov         dword ptr[eax], NO
			Done :
	}

}
