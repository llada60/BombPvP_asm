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
	// ��������ʼ��
	mainScene = new CMainScene;
	if (mainScene != NULL) mainScene->MainSceneInit(m_hIns);
	else MessageBox(NULL, TEXT("��������ʧ��"), TEXT("��ʾ"),MB_OK | MB_ICONERROR);

	// ������Ӧ��������
	playMusic = new CPlayMusic;
	if (playMusic != NULL)
	{
		this->PlayBackMusic();
	}
	else
	{
		MessageBox( NULL, TEXT("���ּ���ʧ��!"), TEXT("��ʾ"), MB_OK | MB_ICONERROR );
	}
}

void CBnbApp::OnGameDraw()
{
	HDC hdc = GetDC(m_hMainWnd);

	// �����������
	HDC hdcMem = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,800,600);
	SelectObject(hdcMem,hBitmap);

	// ��ͼ����ͬ����
	if (this->m_seclectScene == TWO_GAME_SCENE && (twoGameScene != NULL))
	{
		twoGameScene->TwoGameSceneShow(hdcMem);
	}
	else if (this->m_seclectScene == HELP_GAME_SCENE && (helpScene != NULL))
	{
		helpScene->HelpSceneShow(hdcMem);
	}
	else
	{
		mainScene->MainSceneShow(hdcMem);
	}

	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	ReleaseDC(m_hMainWnd,hdc);
}

void CBnbApp::OnGameRun(WPARAM nTimerID)
{
	if (m_seclectScene == TWO_GAME_SCENE && (twoGameScene != NULL))
	{
		twoGameScene->OnTwoGameRun(nTimerID);
	}
	//�ػ�
	this->OnGameDraw();
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
	if (twoGameScene != NULL)
	{
		twoGameScene->OnKeyUp(nKey);
	}
}

void CBnbApp::OnLButtonDown(POINT point)
{
	if (twoGameScene != NULL)
	{
		//��ʱ����˫����Ϸ�İ���ʵ�ְ������³�����
		twoGameScene->OnLButtonDown(m_hIns,point);
	}
}

void CBnbApp::OnLButtonUp(POINT point)
{
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
		if ( MessageBox( NULL, TEXT("ȷ�Ϸ������˵���"), \
			TEXT("�������˵�"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			if (this->m_seclectScene == TWO_GAME_SCENE)
			{
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
		}
	}

	// �ػ�
	this->OnGameDraw();
}

void CBnbApp::OnMouseMove(POINT point)
{
	//��ǰ����Ϊ����������£��������λ�ã����Ƿ�������������ĳ��ѡ��
	if (m_seclectScene == MAIN_SCENE)
	{
		mainScene->MouseMove(point);
	}

	//��ǰ����Ϊ������������£��������λ�ã����Ƿ������ڷ���ѡ��
	if (m_seclectScene == HELP_GAME_SCENE)
	{
		helpScene->MouseMove(point);
	}

	// ��ǰ����Ϊ��Ϸ��������£��������λ�ã����Ƿ��������Ƴ�ѡ��
	if (m_seclectScene == TWO_GAME_SCENE )
	{
		twoGameScene->MouseMove(point);
	}

	// �ػ�
	this->OnGameDraw();
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
		if ( MessageBox( NULL, TEXT("ȷ���˳���Ϸ��"), \
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
	// F8������ ���Ż�ֹͣ��������
	if (this->isKey_stopMusic)
	{
		if(!playMusic->isStop)
		{
			playMusic->SotpBackMusic();

			// ɾ���������ֶ���
			delete playMusic;
			playMusic = NULL;
		}
		else
		{
			if (playMusic != NULL)
			{
				if(this->m_seclectScene == TWO_GAME_SCENE) playMusic->PlayBackMusic(TWOGAME_BACK_MUSIC);
				else playMusic->PlayBackMusic(MAIN_BACK_MUSIC);
			}
		}
	}

	// F8��δ���� ���ݳ������Ų�ͬ��������
	else
	{
		if(this->m_seclectScene == TWO_GAME_SCENE) playMusic->PlayBackMusic(TWOGAME_BACK_MUSIC);
		else playMusic->PlayBackMusic(MAIN_BACK_MUSIC);
	}
}
