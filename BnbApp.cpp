#include "BnbApp.h"
#include <stdio.h>

IMPLEMENT(CBnbApp)

CBnbApp::CBnbApp()
{
	m_seclectScene = MAIN_SCENE;
	isKey_stopMusic = false;

	mainScene = NULL;
	helpScene = NULL;
	twoGameScene = NULL;
	playMusic = NULL;

}

CBnbApp::~CBnbApp()
{
	delete mainScene;
	delete twoGameScene;
	delete helpScene;
	delete playMusic;
	mainScene = NULL;
	helpScene = NULL;
	twoGameScene = NULL;
	playMusic = NULL;
}

void CBnbApp::OnCreateGame()
{
	// 各场景初始化
	mainScene = new CMainScene;
	static TCHAR sznotece[] = TEXT("提示");
	static TCHAR szGame[] = TEXT("场景加载失败");
	static TCHAR szMusic[] = TEXT("音乐加载失败!");
	int x;
	__asm {
		mov  dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 0Ch], 0
		je  M1
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 8]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx + 0Ch]
		call CMainScene::MainSceneInit
		mov  esp, dword ptr[x]
		jmp Conti
		M1 :
		push 10h
			push offset sznotece
			push offset szGame
			push 0
			call MessageBox
			mov  esp, dword ptr[x]
			Conti:

	}
	// 播放相应背景音乐
	playMusic = new CPlayMusic;
	__asm {
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 18h], 0
		je  M2
		mov ecx, dword ptr[this]
		call CBnbApp::PlayBackMusic
		jmp End2
		M2 :
		push 10h
			push offset sznotece
			push offset szMusic
			push 0
			call MessageBox
			mov  esp, dword ptr[x]
			End2:
	}
}

void CBnbApp::OnGameDraw()
{
	HDC hdc;
	HDC hdcMem;
	HBITMAP hBitmap;
	int x;
	__asm {

		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 4]
		push ecx
		call GetDC
		mov dword ptr[hdc], eax
		mov esp, dword ptr[x]

		mov eax, dword ptr[hdc]
		push eax
		call CreateCompatibleDC
		mov dword ptr[hdcMem], eax
		mov esp, dword ptr[x]

		push 258h
		push 320h
		mov eax, dword ptr[hdc]
		push eax
		call CreateCompatibleBitmap
		mov dword ptr[hBitmap], eax
		mov esp, dword ptr[x]

		mov eax, dword ptr[hBitmap]
		push eax
		mov ecx, dword ptr[hdcMem]
		push ecx
		call SelectObject
		mov esp, dword ptr[x]

		mov eax, dword ptr[this]
		cmp dword ptr[eax + 1Ch], 1
		jne LIF
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 10h], 0
		je LIF
		mov eax, dword ptr[hdcMem]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx + 10h]
		call CTwoGameScene::TwoGameSceneShow
		mov esp, dword ptr[x]
		jmp Endif
		LIF :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 2
			jne ELSE
			mov eax, dword ptr[this]
			cmp dword ptr[eax + 14h], 0
			je  ELSE
			mov eax, dword ptr[hdcMem]
			push eax
			mov ecx, dword ptr[this]
			mov ecx, dword ptr[ecx + 14h]
			call CHelpScene::HelpSceneShow
			mov esp, dword ptr[x]
			jmp Endif
			ELSE :
			mov eax, dword ptr[hdcMem]
			push eax
			mov ecx, dword ptr[this]
			mov ecx, dword ptr[ecx + 0Ch]
			call CMainScene::MainSceneShow
			mov esp, dword ptr[x]
			Endif:
			push 0CC0020h
			push 0
			push 0
			mov eax, dword ptr[hdcMem]
			push eax
			push 258h
			push 320h
			push 0
			push 0
			mov ecx, dword ptr[hdc]
			push ecx
			call BitBlt
			mov esp, dword ptr[x]
			mov eax, dword ptr[hdcMem]
			push eax
			call DeleteDC
			mov esp, dword ptr[x]
			mov eax, dword ptr[hBitmap]
			push eax
			call DeleteObject
			mov esp, dword ptr[x]
			mov eax, dword ptr[hdc]
			push eax
			mov ecx, dword ptr[this]
			mov ecx, dword ptr[ecx + 4]
			push ecx
			call ReleaseDC
			mov esp, dword ptr[x]

	}
}

void CBnbApp::OnGameRun(WPARAM nTimerID)
{
	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 1Ch], 1
		jne End
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 10h], 1
		je  End
		mov eax, dword ptr[nTimerID]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx + 10h]
		call CTwoGameScene::OnTwoGameRun
	End:
		mov esp, dword ptr[x]
		mov eax, dword ptr[this]
		mov edx, dword ptr[eax]
		mov ecx, dword ptr[this]
		mov eax, dword ptr[edx + 8]
		call eax
		mov esp, dword ptr[x]
	}
}

void CBnbApp::OnKeyDown(WPARAM nKey)
{
	switch (nKey)
	{
		// F3键： 当在双人游戏界面按下F3可返回主场景 MAIN_SCENE
	case VK_F3:
		if (this->m_seclectScene == TWO_GAME_SCENE)
		{
			// 如果鼠标停留退出选项 返回主场景 需将标记位置为 false
			if (twoGameScene->m_isSelect)
			{
				twoGameScene->m_isSelect = false;
			}

			// 切换回主场景
			if (mainScene == NULL)
			{
				mainScene = new CMainScene;
				mainScene->MainSceneInit(m_hIns);
			}
			m_seclectScene = MAIN_SCENE;

			// 释放游戏场景对象
			delete twoGameScene;
			twoGameScene = NULL;

			this->OnGameDraw();

			// 播放相应背景音乐
			if (!this->isKey_stopMusic)
			{
				this->PlayBackMusic();
			}
		}
		break;

		// F8键 背景音乐开关
	case VK_F8:
		if (this->isKey_stopMusic)
		{
			playMusic = new CPlayMusic;
			this->isKey_stopMusic = false;
		}

		else
		{
			this->isKey_stopMusic = true;
		}
		this->PlayBackMusic();
		break;
	}

	// 将按键传入游戏场景
	if (twoGameScene != NULL)
	{
		twoGameScene->OnKeyDown(nKey);
	}
}

void CBnbApp::OnKeyUp(WPARAM nKey)
{
	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 10h], 0
		je End
		mov eax, dword ptr[nKey]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx + 10h]
		call CTwoGameScene::OnKeyUp
		mov esp, dword ptr[x]
		End:

	}
}

void CBnbApp::OnLButtonDown(POINT point)
{
	/*
		按键放泡泡
	*/
	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 10h], 0
		je End1
		mov eax, dword ptr[ebp + 0Ch]
		push eax
		mov ecx, dword ptr[point]
		push ecx
		mov edx, dword ptr[this]
		mov eax, dword ptr[edx + 8]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx + 10h]
		call CTwoGameScene::OnLButtonDown
		mov esp, dword ptr[x]
		End1:

	}
}

void CBnbApp::OnLButtonUp(POINT point)
{
	// 如果当前场景为主场景并且鼠标在可选范围内，鼠标左键才允许选择不同场景
	if (m_seclectScene == MAIN_SCENE && (mainScene->m_seclectNum == TWO_GAME || mainScene->m_seclectNum == HELP_GAME || mainScene->m_seclectNum == QUIT_GAME))
	{
		this->ChangeScene();
	}

	// 如果当前场景为帮助场景并且鼠标在返回框内，鼠标左键才允许返回主场景
	if (m_seclectScene == HELP_GAME_SCENE && helpScene->m_isSelect)
	{
		if (mainScene == NULL)
		{
			mainScene = new CMainScene;
			mainScene->MainSceneInit(m_hIns);
		}

		m_seclectScene = MAIN_SCENE;
		helpScene->m_isSelect = false; // 返回后将帮助场景的鼠标位置标记置为false

		// 释放帮助场景对象
		if (helpScene)
		{
			delete helpScene;
			helpScene = NULL;
		}
	}

	if (m_seclectScene == TWO_GAME_SCENE && twoGameScene->m_isSelect)
	{
		if (MessageBox(NULL, TEXT("确认返回主菜单？"), \
			TEXT("返回主菜单"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			if (this->m_seclectScene == TWO_GAME_SCENE)
			{
				// 切换回主场景
				if (mainScene == NULL)
				{
					mainScene = new CMainScene;
					mainScene->MainSceneInit(m_hIns);
				}
				m_seclectScene = MAIN_SCENE;

				// 释放游戏场景对象
				delete twoGameScene;
				twoGameScene = NULL;

				this->OnGameDraw();

				// 播放相应背景音乐
				if (!this->isKey_stopMusic)
				{
					this->PlayBackMusic();
				}
			}
		}
	}

	// 重绘
	this->OnGameDraw();
}

void CBnbApp::OnMouseMove(POINT point)
{
	/*
		根据鼠标指针切换场景
	*/
	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax + 1Ch], 0
		jne E6
		mov eax, dword ptr[ebp + 0Ch]
		push eax
		mov ecx, dword ptr[point]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx + 0Ch]
		call CMainScene::MouseMove
		E6 :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 2
			jne F82
			mov eax, dword ptr[ebp + 0Ch]
			push eax
			mov ecx, dword ptr[point]
			push ecx
			mov edx, dword ptr[this]
			mov ecx, dword ptr[edx + 14h]
			call CHelpScene::MouseMove
		F82:
			mov eax, dword ptr[this]
			cmp dword ptr[eax+1Ch], 1
			jne End
		NIF :
			mov eax, dword ptr[ebp + 0Ch]
			push eax
			mov ecx, dword ptr[point]
			push ecx
			mov edx, dword ptr[this]
			mov ecx, dword ptr[edx + 10h]
			call CTwoGameScene::MouseMove
			End :
		mov eax, dword ptr[this]
			mov edx, dword ptr[eax]
			mov ecx, dword ptr[this]
			mov eax, dword ptr[edx + 8]
			call eax
			mov esp, dword ptr[x]
	}
}

void CBnbApp::ChangeScene()
{
	// 鼠标点击后 根据鼠标悬浮的标记 判断应切换到哪个场景
	if (mainScene->m_seclectNum == TWO_GAME)
	{
		// 创建游戏场景对象并初始化
		if (twoGameScene == NULL)
		{
			twoGameScene = new CTwoGameScene;
			twoGameScene->TwoGameSceneInit(m_hIns, m_hMainWnd);
		}

		this->m_seclectScene = TWO_GAME_SCENE;

		// 释放主场景对象
		if (mainScene)
		{
			delete mainScene;
			mainScene = NULL;
		}
	}
	else if (mainScene->m_seclectNum == HELP_GAME)
	{
		// 创建帮助场景对象并初始化
		if (helpScene == NULL)
		{
			helpScene = new CHelpScene;
			helpScene->HelpSceneInit(m_hIns);
		}

		this->m_seclectScene = HELP_GAME_SCENE;

		// 释放主场景对象
		if (mainScene)
		{
			delete mainScene;
			mainScene = NULL;
		}
	}
	else if (mainScene->m_seclectNum == QUIT_GAME)
	{
		if (MessageBox(NULL, TEXT("确认退出游戏？"), \
			TEXT("退出"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			PostQuitMessage(0);
		}
		else
		{
			this->m_seclectScene = MAIN_SCENE;
		}
	}

	// 主场景进去帮助场景，背景音乐不变
	if (this->m_seclectScene != HELP_GAME_SCENE && (!this->isKey_stopMusic))
	{
		this->PlayBackMusic();
	}

	// 重绘
	this->OnGameDraw();
}

void CBnbApp::PlayBackMusic()
{
	/*
		F8键按下 播放或停止背景音乐
	*/ 
	
	static TCHAR szSound[] = TEXT("sounds/bula.wav");
	static TCHAR szSound1[] = TEXT("sounds/back_cool.wav");
	static TCHAR szSound2[] = TEXT("sounds/main_back.wav");

	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		movzx ecx, byte ptr[eax + 20h]
		test ecx, ecx
		je  B2
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 18h]
		movzx edx, byte ptr[ecx]
		test edx, edx
		jne Music
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 18h]
		call CPlayMusic::SotpBackMusic
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax + 18h]
		mov dword ptr[ebp - 0D4h], ecx
		cmp dword ptr[ebp - 0D4h], 0
		je B4
		push 1
		mov ecx, dword ptr[ebp - 0D4h]
		call CPlayMusic::~CPlayMusic
		mov dword ptr[ebp - 0DCh], eax
		jmp NB5
		B4 :
		mov dword ptr[ebp - 0DCh], 0
			NB5 :
			mov eax, dword ptr[this]
			mov dword ptr[eax + 18h], 0
			jmp End
			Music :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 18h], 0
			je End
			mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 1
			jne B5
			push offset szSound
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
			B5 :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 2
			jne A0
			push offset szSound1
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
			A0 :
		push offset szSound2
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
			B2 :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 1
			jne CD
			push offset szSound
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
			CD :
		mov eax, dword ptr[this]
			cmp dword ptr[eax + 1Ch], 2
			jne E8
			push offset szSound1
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
			E8 :
		push offset szSound2
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic

			End :
		mov esp, dword ptr[x]
	}
}
