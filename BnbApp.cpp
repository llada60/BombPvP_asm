#include "BnbApp.h"

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
	// ��������ʼ��
	mainScene = new CMainScene;
	static TCHAR sznotece[] = TEXT("��ʾ");
	static TCHAR szGame[] = TEXT("��������ʧ��");
	static TCHAR szMusic[] = TEXT("���ּ���ʧ��!");
	int x;
	__asm {		
		mov  dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax+0Ch], 0
		je  M1
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+8]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx+0Ch]
		call CMainScene::MainSceneInit
		mov  esp, dword ptr[x]
		jmp Conti
	M1:
		push 10h
		push offset sznotece
		push offset szGame
		push 0
		call MessageBox
		mov  esp, dword ptr[x]
	Conti:

	}
	// ������Ӧ��������
	playMusic = new CPlayMusic;
	__asm {
		mov eax, dword ptr[this]
		cmp dword ptr[eax+18h], 0
		je  M2
		mov ecx, dword ptr[this]
		call CBnbApp::PlayBackMusic
		jmp End2
	M2:
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
		mov ecx, dword ptr[eax+4]
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
		cmp dword ptr[eax+1Ch],1
		jne LIF
		mov eax, dword ptr[this]
		cmp dword ptr[eax+10h],0
		je LIF
		mov eax, dword ptr[hdcMem]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+10h]
		call CTwoGameScene::TwoGameSceneShow
		mov esp, dword ptr[x]
		jmp Endif
	LIF:
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 2
		jne LIF1
		mov eax, dword ptr[this]
		cmp dword ptr[eax+10h], 0
		je  LIF1
		mov eax, dword ptr[hdcMem]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+10h]
		call CTwoGameScene::TwoGameSceneShow
		mov esp, dword ptr[x]
		jmp Endif
	LIF1:
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 3
		jne ELSE
		mov eax, dword ptr[this]
		cmp dword ptr[eax+14h], 0
		je  ELSE
		mov eax, dword ptr[hdcMem]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+14h]
		call CHelpScene::HelpSceneShow
		mov esp, dword ptr[x]
		jmp Endif
	ELSE:
		mov eax, dword ptr[hdcMem]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+0Ch]
		call CMainScene::MainSceneShow
		mov esp, dword ptr[x]
	Endif:
		push 0CC0020h
		push 0
		push 0
		mov eax,dword ptr[hdcMem]
		push eax
		push 258h
		push 320h
		push 0
		push 0
		mov ecx,dword ptr[hdc]
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
		mov ecx, dword ptr[ecx+4]
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
		cmp dword ptr[eax+1Ch], 2
		je  OR1
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 1
		jne Deal
	OR1:	
		mov eax, dword ptr[this]
		cmp dword ptr[eax+10h], 0
		je  Deal
	Deal:
		mov eax, dword ptr[nTimerID]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+10h]
		call CTwoGameScene::OnTwoGameRun
		mov esp, dword ptr[x]
		mov eax, dword ptr[this]
		mov edx, dword ptr[eax]
		mov ecx, dword ptr[this]
		mov eax, dword ptr[edx+8]
		call eax
		mov esp, dword ptr[x]
	}
}

void CBnbApp::OnKeyDown(WPARAM nKey)
{
	switch (nKey)
	{
	// F3���� ����˫����Ϸ���水��F3�ɷ��������� MAIN_SCENE
	case VK_F3:
		if (this->m_seclectScene == TWO_GAME_SCENE )
		{
			// ������ͣ���˳�ѡ�� ���������� �轫���λ��Ϊ false
			if (twoGameScene->m_isSelect)
			{
				twoGameScene->m_isSelect = false;
			}

			// �л���������
			if (mainScene == NULL)
			{
				mainScene = new CMainScene;
				mainScene->MainSceneInit(m_hIns);
			}
			m_seclectScene = MAIN_SCENE;

			// �ͷ���Ϸ��������
			delete twoGameScene;
			twoGameScene = NULL;

			this->OnGameDraw();

			// ������Ӧ��������
			if (!this->isKey_stopMusic)
			{
				this->PlayBackMusic();
			}
		}
		break;

	// F8�� �������ֿ���
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

	// ������������Ϸ����
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
		cmp dword ptr[eax+10h], 0
		je End
		mov eax, dword ptr[nKey]
		push eax
		mov ecx, dword ptr[this]
		mov ecx, dword ptr[ecx+10h]
		call CTwoGameScene::OnKeyUp
		mov esp, dword ptr[x]
	End:

	}
}

void CBnbApp::OnLButtonDown(POINT point)
{
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
	//static TCHAR szno[] = TEXT("�˳�");
	//static TCHAR sznoti[] = TEXT("���ˣ� ��Ϸ���ڽ���, ȷ���˳�ô?");
	//int x;

	//__asm {
	//	mov dword ptr[x], esp
	//	// �����ǰ����Ϊ��������������ڿ�ѡ��Χ�ڣ�������������ѡ��ͬ����
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 1Ch], 0
	//	jne E46
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 0Ch]
	//	cmp dword ptr[ecx], 1
	//	je  E3
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 0Ch]
	//	cmp dword ptr[ecx], 2
	//	je  E3
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 0Ch]
	//	cmp dword ptr[ecx], 3
	//	je  E3
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 0Ch]
	//	cmp dword ptr[ecx], 4
	//	jne E46
	//		// this->ChangeScene();
	//		E3:
	//	mov ecx, dword ptr[this]
	//	call CBnbApp::ChangeScene

	//	// �����ǰ����Ϊ����������������ڷ��ؿ��ڣ���������������������
	//			E46:
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 1Ch], 3
	//	jne NEXTIF
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 14h]
	//	movzx edx, byte ptr[ecx]
	//	test edx, edx
	//	je NEXTIF
	//	//if (mainScene == NULL)
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 0Ch], 0
	//	jne MIANS
	//	//	mainScene = new CMainScene;
	//	push 28h
	//	//call operator new
	//	//add  esp, 4
	//	mov dword ptr[ebp - 0ECh], eax
	//	mov dword ptr[ebp - 4], 0
	//	cmp dword ptr[ebp - 0ECh], 0
	//	je  NEW
	//	mov ecx, dword ptr[ebp - 0ECh]
	//	call CMainScene::CMainScene
	//	mov dword ptr[ebp - 100h], eax
	//	jmp NEW2
	//		NEW :
	//	mov dword ptr[ebp - 100h], 0
	//		NEW2 :
	//	mov eax, dword ptr[ebp - 100h]
	//	mov dword ptr[ebp - 0E0h], eax
	//	mov dword ptr[ebp - 4], 0FFFFFFFFh
	//	mov ecx, dword ptr[this]
	//	mov edx, dword ptr[ebp - 0E0h]
	//	mov dword ptr[ecx + 0Ch], edx
	//	// mainScene->MainSceneInit(m_hIns);
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 8]
	//	push ecx
	//	mov edx, dword ptr[this]
	//	mov ecx, dword ptr[edx + 0Ch]
	//	call CMainScene::MainSceneInit

	//		MIANS :
	//	//m_seclectScene = MAIN_SCENE;
	//	mov eax, dword ptr[this]
	//	mov dword ptr[eax + 1Ch], 0
	//	//	helpScene->m_isSelect = false; // ���غ󽫰������������λ�ñ����Ϊfalse
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 14h]
	//	mov byte ptr[ecx], 0

	//		// �ͷŰ�����������
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 14h], 0
	//	je  NEXRIF
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 14h]
	//	mov dword ptr[ebp - 0F8h], ecx
	//	cmp dword ptr[ebp - 0F8h], 0
	//	je  DEA
	//	push 1
	//	mov ecx, dword ptr[ebp - 0F8h]
	//	call CHelpScene::~CHelpScene
	//	mov dword ptr[ebp - 100h], eax
	//	jmp DEA2
	//	DEA :
	//	mov dword ptr[ebp - 100h], 0
	//// helpScene = NULL;
	//	DEA2:
	//	mov eax, dword ptr[this]
	//	mov dword ptr[eax + 14h], 0
	//	NEXRIF:
	//	//if ((m_seclectScene == TWO_GAME_SCENE || m_seclectScene == ONE_GAME_SCENE) && twoGameScene->m_isSelect)
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 1Ch], 2
	//	je  L1
	//	mov eax, dword ptr[this]
	//	cmp dword ptr[eax + 1Ch], 1
	//	jne DRAW
	//	L1 :
	//	mov eax, dword ptr[this]
	//	mov ecx, dword ptr[eax + 10h]
	//	movzx edx, byte ptr[ecx + 7BCh]
	//	test edx, edx
	//	je  DRAW

	//	//			if (MessageBox(NULL, TEXT("���ˣ� ��Ϸ���ڽ���, ȷ���˳�ô?"), \
	//			TEXT("�˳�"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)

	//	push 21h
	//	push offset szno
	//	push offset sznoti
	//	push 0
	//	call MessageBox
	//	mov esp, dword ptr[x]
	//	cmp eax, 1
	//	jne DRAW
	//// PostQuitMessage(0);

	//	push 0
	//	call PostQuitMessage
	//	mov esp, dword ptr[x]


	//// �ػ�
	//// this->OnGameDraw();
	//DRAW:
	//	mov eax, dword ptr[this]
	//	mov edx, dword ptr[eax]
	//	mov ecx, dword ptr[this]
	//	mov eax, dword ptr[edx + 8]
	//	call eax
	//	mov esp, dword ptr[x]
	//}




	// �����ǰ����Ϊ��������������ڿ�ѡ��Χ�ڣ�������������ѡ��ͬ����
	if (m_seclectScene == MAIN_SCENE && (mainScene->m_seclectNum == TWO_GAME || mainScene->m_seclectNum == HELP_GAME || mainScene->m_seclectNum == QUIT_GAME))
	{
		this->ChangeScene();
	}

	// �����ǰ����Ϊ����������������ڷ��ؿ��ڣ���������������������
	if (m_seclectScene == HELP_GAME_SCENE && helpScene->m_isSelect)
	{
		if (mainScene == NULL)
		{
			mainScene = new CMainScene;
			mainScene->MainSceneInit(m_hIns);
		}

		m_seclectScene = MAIN_SCENE;
		helpScene->m_isSelect = false; // ���غ󽫰������������λ�ñ����Ϊfalse

		// �ͷŰ�����������
		if (helpScene)
		{
			delete helpScene;
			helpScene = NULL;
		}
	}

	if (m_seclectScene == TWO_GAME_SCENE && twoGameScene->m_isSelect)
	{
		if ( MessageBox( NULL, TEXT("���ˣ� ��Ϸ���ڽ���, ȷ���˳�ô?"), \
			TEXT("�˳�"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
	}

	// �ػ�
	this->OnGameDraw();
}

void CBnbApp::OnMouseMove(POINT point)
{
	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 0
		jne E6
		mov eax, dword ptr[ebp+0Ch]
		push eax
		mov ecx, dword ptr[point]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx+0Ch]
		call CMainScene::MouseMove
		E6:
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 3
		jne NIF
		mov eax, dword ptr[ebp+0Ch]
		push eax
		mov ecx, dword ptr[point]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx+14h]
		call CHelpScene::MouseMove
		NIF:
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 2
		je  Dea
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 1
		jne End
			Dea:
		mov eax, dword ptr[ebp+0Ch]
		push eax
		mov ecx, dword ptr[point]
		push ecx
		mov edx, dword ptr[this]
		mov ecx, dword ptr[edx+10h]
		call CTwoGameScene::MouseMove
			End:
		mov eax, dword ptr[this]
		mov edx, dword ptr[eax]
		mov ecx, dword ptr[this]
		mov eax, dword ptr[edx+8]
		call eax
		mov esp, dword ptr[x]
	}
}

void CBnbApp::ChangeScene()
{
	// ������� ������������ı�� �ж�Ӧ�л����ĸ�����
	if (mainScene->m_seclectNum == TWO_GAME)
	{
		// ������Ϸ�������󲢳�ʼ��
		if (twoGameScene == NULL)
		{
			twoGameScene = new CTwoGameScene;
			twoGameScene->TwoGameSceneInit(m_hIns,m_hMainWnd);
		}

		this->m_seclectScene = TWO_GAME_SCENE;

		// �ͷ�����������
		if (mainScene)
		{
			delete mainScene;
			mainScene = NULL;
		}
	}
	else if (mainScene->m_seclectNum == HELP_GAME)
	{
		// ���������������󲢳�ʼ��
		if (helpScene == NULL)
		{
			helpScene = new CHelpScene;
			helpScene->HelpSceneInit(m_hIns);
		}
		
		this->m_seclectScene = HELP_GAME_SCENE;

		// �ͷ�����������
		if (mainScene)
		{
			delete mainScene;
			mainScene = NULL;
		}
	}
	else if (mainScene->m_seclectNum == QUIT_GAME)
	{
		if ( MessageBox( NULL, TEXT("���ˣ� ��Ĳ�������ô? ������˼����"), \
			TEXT("�˳�"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
		else
		{
			this->m_seclectScene = MAIN_SCENE;
		}
	}

	// ��������ȥ�����������������ֲ���
	if (this->m_seclectScene != HELP_GAME_SCENE && (!this->isKey_stopMusic))
	{
		this->PlayBackMusic();
	}

	// �ػ�
	this->OnGameDraw();
}

void CBnbApp::PlayBackMusic()
{
	static TCHAR szSound[] = TEXT("sounds/back_mydream.wav");
	static TCHAR szSound1[] = TEXT("sounds/back_cool.wav");
	static TCHAR szSound2[] = TEXT("sounds/main_back.wav");

	int x;
	__asm {
		mov dword ptr[x], esp
		mov eax, dword ptr[this]
		movzx ecx, byte ptr[eax+20h]
		test ecx, ecx
		je  B2
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+18h]
		movzx edx, byte ptr[ecx]
		test edx, edx
		jne Music
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+18h]
		call CPlayMusic::SotpBackMusic
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+18h]
		mov dword ptr[ebp-0D4h], ecx
		cmp dword ptr[ebp-0D4h], 0
		je B4
		push 1
		mov ecx, dword ptr[ebp-0D4h]
		call CPlayMusic::~CPlayMusic
		mov dword ptr[ebp-0DCh], eax
		jmp NB5
		B4:
			mov dword ptr[ebp-0DCh], 0
		NB5:	
			mov eax, dword ptr[this]
			mov dword ptr[eax+18h], 0
			jmp End
		Music:
		mov eax, dword ptr[this]
		cmp dword ptr[eax+18h], 0
		je End
		mov eax, dword ptr[this]
		cmp dword ptr[eax+1Ch], 1
		jne B5
		push offset szSound
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+18h]
		call CPlayMusic::PlayBackMusic
		jmp End
		B5:
			mov eax, dword ptr[this]
			cmp dword ptr[eax+1Ch], 2
			jne A0
			push offset szSound1
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax+18h]
			call CPlayMusic::PlayBackMusic
			jmp End
		A0:
			push offset szSound2
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax+18h]
			call CPlayMusic::PlayBackMusic
		jmp End
		B2:
			mov eax, dword ptr[this]
			cmp dword ptr[eax+1Ch],1
			jne CD
			push offset szSound
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax+18h]
			call CPlayMusic::PlayBackMusic
			jmp End
		CD:
			mov eax, dword ptr[this]
			cmp dword ptr[eax+1Ch], 2
			jne E8
			push offset szSound1
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax + 18h]
			call CPlayMusic::PlayBackMusic
			jmp End
		E8:
			push offset szSound2
			mov eax, dword ptr[this]
			mov ecx, dword ptr[eax+18h]
			call CPlayMusic::PlayBackMusic

		End:
			mov esp, dword ptr[x]
	}
}
