#include "TwoGameScene.h"

CTwoGameScene::CTwoGameScene()
{
	m_bitmap_gameBack = NULL;
	m_bitmap_road = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
	m_bitmap_statusInfo = NULL;
	m_bitmap_win_word = NULL;
	m_isSelect = false;
	m_gameTime = 0;
	m_statusInfo_y = 0;

	m_twoGameWnd = NULL;
	m_twoGameHIns = NULL;
	m_gameStatus = NO_SHOW;
}

CTwoGameScene::~CTwoGameScene()
{
	DeleteObject(m_bitmap_gameBack);
	DeleteObject(m_bitmap_road);
	DeleteObject(m_bitmap_quit);
	DeleteObject(m_bitmap_quit_select);
	DeleteObject(m_bitmap_timeNum);
	DeleteObject(m_bitmap_statusInfo);
	DeleteObject(m_bitmap_win_word);

	m_bitmap_gameBack = NULL;
	m_bitmap_road = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
	m_bitmap_statusInfo = NULL;
	m_bitmap_win_word = NULL;
}

void CTwoGameScene::TwoGameSceneInit(HINSTANCE hIns, HWND hWnd)
{
	m_twoGameHIns = hIns;
	m_twoGameWnd = hWnd;
	m_bitmap_gameBack = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GAME_BACK));
	m_bitmap_road = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ROAD));
	m_bitmap_quit = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME));
	m_bitmap_quit_select = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME_SELECT));
	m_bitmap_timeNum = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TIME_NUMBER));
	m_bitmap_statusInfo = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GAMEOVER_WORD));
	m_bitmap_win_word = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_NUM_WORD));

	m_gameTime = 300;      // ����ʱ������ 300s
	m_statusInfo_y = 70;   // ����Ĭ��λ�� y = 70
	m_gameStatus = START;  // ��Ϸ��ʼ ��ʾ��Ϸ��ʼ����

	// ��ʼ����ͼ
	gameMap.MapInit(hIns);

	//��ʼ������
	prop.PropInit(hIns,gameMap);

	// ��ʼ����Ϸ����
	playerOne.PlayerInit(hIns);
	playerTwo.PlayerInit(hIns);

	// ������ʱ��
	SetTimer(m_twoGameWnd, STOPSOUND_TIMER_ID, 10, NULL);
	SetTimer(m_twoGameWnd, BUBBLE_CHANGE_TIMER_ID, 200, NULL);
	SetTimer(m_twoGameWnd, GAME_TIME_TIMER_ID, 1000, NULL);
	SetTimer(m_twoGameWnd, STATUS_INFO_TIMER_ID, 80, NULL);
	SetTimer(m_twoGameWnd, PLAYERSTART_TIMER_ID,50, NULL);
	SetTimer(m_twoGameWnd, WIND_TIMER_ID,500, NULL);
	SetTimer(m_twoGameWnd, PLAYER_MOVE_TIMER_ID,10,NULL);
	SetTimer(m_twoGameWnd,PLAYER_MOVE_SHOW_TIMER_ID,150,NULL);
	SetTimer(m_twoGameWnd, PROPERTY_CHANGR_TIMER_ID, 200, NULL);
	SetTimer(m_twoGameWnd, PROPERTY_BOOM_TIMER_ID, 1000/30, NULL);
	SetTimer(m_twoGameWnd, PLAYERSTART_DIE_ID, 1000/10, NULL);
	// ��Ϸ��ʼ��Ч
	playSound.Play(START_GAME_SOUND);
}

void CTwoGameScene::TwoGameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
	SelectObject(hdcMem,m_bitmap_road);
	BitBlt(hdc,20,41,600,520,hdcMem,0,0,SRCCOPY);

	// �˳���ť
	if (m_isSelect)
	{
		SelectObject(hdcMem,m_bitmap_quit_select);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_quit);
	}

	BitBlt(hdc,650,556,130,30,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);

	// ������ʾ
	this->AllBubbleShow(hdc);
	// ��ը������ʾ
	this->AllBoomShow(hdc);

	//������ʾ
	prop.PropPositionShow(hdc);

	// ��ͼ��ʾ
	gameMap.MapShow(hdc);

	// ����ʱ
	this->ShowTime(hdc);

	//���������ʾ
	playerOne.PlayerShow(hdc);
	playerTwo.PlayerShow(hdc);

	gameMap.MapUpShow(hdc);
	// ������Ϸ�����в����øú�����ֻҪ��Ϸ��ʼ����ʱ������ʱ�����ϵ���
	if (m_gameStatus != NO_SHOW)
	{
		this->ShowGameStatus(hdc);
	}
}

void CTwoGameScene::MouseMove(POINT point)
{
	if (point.x > 650 && point.x < 780 && point.y > 556 && point.y < 586)
	{
		m_isSelect = true;
	}
	else
	{
		m_isSelect = false;
	}
}

void CTwoGameScene::OnKeyDown(WPARAM nKey)
{
	switch (nKey)
	{
	// �ر���Ч
	case VK_F7:
		if (playSound.isKeyToStop)
		{
			playSound.isKeyToStop = false;
			SetTimer(m_twoGameWnd,STOPSOUND_TIMER_ID,10,NULL);
		}
		else 
		{
			playSound.isKeyToStop = true;
			KillTimer(m_twoGameWnd,STOPSOUND_TIMER_ID);
		}		
		break;
	// ���һ��������
	case  VK_SPACE:
		// �������� �����һ�ѷ��õ�����
		{
			auto ite = m_lstBubble.begin();
			int tempNum = 0;
			while (ite != m_lstBubble.end())
			{
				if ((*ite)->m_bubble_owner == OWNER_PLAYERONE)
				{
					tempNum++;
				}
				ite++;
			}
			if (tempNum < playerOne.m_bubbleNum)
			{
				playerOne.CreateBubble(m_twoGameHIns,gameMap,m_lstBubble,playSound,playerOne.m_player_x,playerOne.m_player_y);
			}
		}
		break;
	// ��Ҷ���������
	case VK_SHIFT:
		{
			// �������� ����Ҷ��ѷ��õ�����
			auto ite = m_lstBubble.begin();
			int tempNum = 0;
			while (ite != m_lstBubble.end())
			{
				if ((*ite)->m_bubble_owner == OWNER_PLAYERTWO)
				{
					tempNum++;
				}
				ite++;
			}
			if (tempNum < playerTwo.m_bubbleNum)
			{
				playerTwo.CreateBubble(m_twoGameHIns,gameMap,m_lstBubble,playSound,playerTwo.m_player_x,playerTwo.m_player_y);
			}
		}
		break;
		// ����һ�ƶ�
	
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		{
			// ���ƶ������Ϊtrue
			playerOne.m_bMoveFlag = true;

		}
		break;
		// ������ƶ�
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		{
			// ���ƶ������Ϊtrue
			playerTwo.m_bMoveFlag = true;

		}
		break;
	}
}

void CTwoGameScene::OnKeyUp(WPARAM nKey)
{
	if (nKey == 'W' || nKey == 'A' || nKey == 'S' || 'D')
	{
		playerOne.m_Move_ShowId = 0;
		playerOne.m_bMoveFlag = false;
	}

	if (nKey == VK_LEFT || nKey == VK_RIGHT || nKey == VK_UP || VK_DOWN)
	{
		playerTwo.m_Move_ShowId = 0;
		playerTwo.m_bMoveFlag = false;
	}
}

void CTwoGameScene::OnTwoGameRun(WPARAM nTimerID)
{
	// ֹͣ��Ч
	if (nTimerID == STOPSOUND_TIMER_ID)
	{
		if (playSound.isPlay && (playSound.GetPos() >= playSound.GetFileLen()))
		{
			playSound.Stop();
		}
	}

	// ��������������ʱ��
	if (nTimerID == BUBBLE_CHANGE_TIMER_ID)
	{

		this->ChangeBubbleShowID();

	}
	if (nTimerID == PROPERTY_BOOM_TIMER_ID)
	{

		this->ChangeBoomShowID();

	}

	// �ı䵹��ʱ������--
	if (nTimerID == GAME_TIME_TIMER_ID)
	{
		if (m_gameTime == 0)
		{
			// ����ƽ������
			m_gameStatus = DRAW;
			m_statusInfo_y = 60;

			// ����ƽ����Ч
			playSound.Play(DRAW_GAME_SOUND);

			// �ر����ж�ʱ��
			for(int i = TIMER_BEGIN;i <= TIMER_END;i++)
			{
				KillTimer(m_twoGameWnd ,i);
			}
		}
		else
		{
			m_gameTime--;
		}
	}

	// �ı�����λ��
	if (nTimerID == STATUS_INFO_TIMER_ID)
	{
		if (m_statusInfo_y <= -80)
		{
			KillTimer(m_twoGameWnd,STATUS_INFO_TIMER_ID); // ֹͣ��ʱ��
			m_gameStatus = NO_SHOW;                       // ����Ϸ����״̬�����ΪĬ��
		}
		else
		{
			m_statusInfo_y -= 20;
		}
	}

	// ��ҳ���������ʱ��
	if (nTimerID == PLAYERSTART_TIMER_ID)
	{
		this->ChangePlayerStartShowID();
	}

	// �糵ת��ʱ��
	if (nTimerID == WIND_TIMER_ID)
	{
		if(gameMap.m_nShowID == 1) gameMap.m_nShowID = 0;
		else gameMap.m_nShowID = 1;
	}

	// �����ƶ���ʱ��
	if (nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		// ͨ���ı��ⰴ��ʱ�� �ı��ƶ��ٶ�
		static int one_flag = 10;
		static int two_flag = 10;
		if (one_flag < playerOne.m_speed_timer)
		{
			one_flag += 10;
		}
		else
		{
			if (GetAsyncKeyState('A'))
			{
				playerOne.PlayerMove('A',gameMap,prop,playSound);
			}
			if (GetAsyncKeyState('D'))
			{
				playerOne.PlayerMove('D',gameMap,prop,playSound);
			}
			if (GetAsyncKeyState('W'))
			{
				playerOne.PlayerMove('W',gameMap,prop,playSound);
			}
			if (GetAsyncKeyState('S'))
			{
				playerOne.PlayerMove('S',gameMap,prop,playSound);
			}
			one_flag = 10;
		}

		if (two_flag < playerTwo.m_speed_timer)
		{
			two_flag += 10;
		}
		else
		{
			if (GetAsyncKeyState(VK_LEFT))
			{
				playerTwo.PlayerMove(VK_LEFT,gameMap,prop,playSound);

			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				playerTwo.PlayerMove(VK_RIGHT,gameMap,prop,playSound);

			}
			if (GetAsyncKeyState(VK_UP))
			{
				playerTwo.PlayerMove(VK_UP,gameMap,prop,playSound);
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				playerTwo.PlayerMove(VK_DOWN,gameMap,prop,playSound);
			}
			two_flag = 10;
		}
	}
	// �����ƶ�������ʱ��
	if (nTimerID == PLAYER_MOVE_SHOW_TIMER_ID)
	{		
		if (playerOne.m_bMoveFlag == true)
		{
			if (playerOne.m_Move_ShowId >= 5) playerOne.m_Move_ShowId = 0;
			else playerOne.m_Move_ShowId++;
		}
		if (playerTwo.m_bMoveFlag == true)
		{
			if (playerTwo.m_Move_ShowId >= 5) playerTwo.m_Move_ShowId = 0;
			else playerTwo.m_Move_ShowId++;
		}
	}
	// ���߱仯��ʱ��
	if(nTimerID == PROPERTY_CHANGR_TIMER_ID)
	{
		this->ChangePropShowID();
	}
	// �������
	if(nTimerID == PLAYERSTART_DIE_ID)
	{
		if(playerOne.m_player_status == DIE)
		{
			if(playerOne.m_DieShowID == 1)
			{
				GameOver();
			}else
			{
				playerOne.m_DieShowID--;
			}
		}
		if(playerTwo.m_player_status == DIE)
		{
			if(playerTwo.m_DieShowID == 1)
			{
				GameOver();
			}else
			{
				playerTwo.m_DieShowID--;
			}
		}
	}
}

void CTwoGameScene::OnLButtonDown(HINSTANCE hIns,POINT point)
{
	// �������³����ݣ���괫���Ӧ�ĵ�x,y
	//	this->CreateBubble(hIns, point.x, point.y);
}

void CTwoGameScene::ChangeBubbleShowID()
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		// �ж��������ڼ��Σ���κ���ʧ
		if((*ite_Bubble)->m_nBubbleBj == 0)
		{
			// ������ת���ɶ�Ӧ�����±�
			int i = ((*ite_Bubble)->m_nBubble_y - 40) / 40;
			int j = ((*ite_Bubble)->m_nBubble_x - 20) / 40;
			// ������ͼ�ϰ���
			gameMap.MapBlast(i,j,(*ite_Bubble)->m_nBubble_power,(*ite_Bubble)->m_arrfx);
			//----------------------------------------------------------------
			this->SetFx(ite_Bubble,i,j);

			if(IsKillPlayerOne(ite_Bubble,i,j))  
			{
				playerOne.m_player_status = DIE;

			}
			if(IsKillPlayerTwo(ite_Bubble,i,j))    
			{
				playerTwo.m_player_status = DIE;
			}
			list<CBubble*>::iterator ite_JBubble = m_lstBubble.begin();
			{
				while(ite_JBubble != m_lstBubble.end())
				{
					if(ite_JBubble == ite_Bubble)
					{
						++ite_JBubble;
						continue;
					}
					if(IsButtleBoom(ite_JBubble,ite_Bubble))
					{
						int x = ((*ite_JBubble)->m_nBubble_y - 40) / 40;
						int y = ((*ite_JBubble)->m_nBubble_x - 20) / 40;
						gameMap.MapBlast(x,y,(*ite_JBubble)->m_nBubble_power,(*ite_JBubble)->m_arrfx);
						this->SetFx(ite_JBubble,x,y);
						gameMap.map_type[x][y] = No;
						if(IsKillPlayerOne(ite_JBubble,x,y))  
						{
							playerOne.m_player_status = DIE;

						}
						if(IsKillPlayerTwo(ite_JBubble,x,y))    
						{
							playerTwo.m_player_status = DIE;
						}
						m_lstBoom.push_back(*ite_JBubble);
						ite_JBubble = m_lstBubble.erase(ite_JBubble);
						continue;
					}
					++ite_JBubble;
				}
			}
			//-------------------------------------------------------------------
			// ����ͼ��λ����Ϊ�� �� No
			gameMap.map_type[i][j] = No;
			// ɾ��������
			m_lstBoom.push_back(*ite_Bubble);
			ite_Bubble = m_lstBubble.erase(ite_Bubble);

			playSound.Play(BLAST_SOUND); // ��ը��Ч
		}
		else
		{
			//�ı����ݵ�showidʵ�����������任
			if((*ite_Bubble)->m_nShowID == 0)
			{
				(*ite_Bubble)->m_nShowID = 2;

			}
			else
			{
				((*ite_Bubble)->m_nShowID)--;
			}
			((*ite_Bubble)->m_nBubbleBj)--;

			ite_Bubble++;
		}
	}
}
bool CTwoGameScene::IsButtleBoom(list<CBubble*>::iterator &ite_JBubble, list<CBubble*>::iterator &ite_Bubble)
{
	if ((*ite_JBubble)->m_nBubble_x + 20 > (*ite_Bubble)->m_nBubble_x 
		&& (*ite_JBubble)->m_nBubble_x + 20 < (*ite_Bubble)->m_nBubble_x  + 40
		&& (*ite_JBubble)->m_nBubble_y + 20  > (*ite_Bubble)->m_nBubble_y  - ((*ite_Bubble)->m_arrfx[0])*40
		&& (*ite_JBubble)->m_nBubble_y + 20  < (*ite_Bubble)->m_nBubble_y  + ((*ite_Bubble)->m_arrfx[1])*40
		|| ((*ite_JBubble)->m_nBubble_x + 20  > (*ite_Bubble)->m_nBubble_x - (*ite_Bubble)->m_arrfx[2]*40 
		&& (*ite_JBubble)->m_nBubble_x + 20  < (*ite_Bubble)->m_nBubble_x + (*ite_Bubble)->m_arrfx[3]*40 + 40
		&& (*ite_JBubble)->m_nBubble_y + 20  > (*ite_Bubble)->m_nBubble_y
		&& (*ite_JBubble)->m_nBubble_y + 20  < (*ite_Bubble)->m_nBubble_y + 40))
		return true;
	return false;
}

bool CTwoGameScene::IsKillPlayerOne(list<CBubble*>::iterator &ite_Bubble, int i, int j)
{
	if((playerOne.m_player_x + 20 - 20 > (j)*40 
		&& playerOne.m_player_x + 20 - 20 < (j)*40 + 40
		&& playerOne.m_player_y	+ 20 - 20 > ((i - (*ite_Bubble)->m_arrfx[0]))*40
		&& playerOne.m_player_y + 20 - 20 < ((i + (*ite_Bubble)->m_arrfx[1]))*40 + 40)
		|| (playerOne.m_player_x + 20 - 20 > (j - (*ite_Bubble)->m_arrfx[2])*40 
		&& playerOne.m_player_x + 20 - 20 < (j + (*ite_Bubble)->m_arrfx[3])*40 + 40
		&& playerOne.m_player_y + 20 - 20 > (i)*40
		&& playerOne.m_player_y + 20 - 20 < (i)*40 + 40))
		return true;
	return false;
}
bool CTwoGameScene::IsKillPlayerTwo(list<CBubble*>::iterator &ite_Bubble, int i, int j)
{
	if((playerTwo.m_player_x + 20 - 20 > (j)*40 
		&& playerTwo.m_player_x + 20 - 20 < (j)*40 + 40
		&& playerTwo.m_player_y	+ 20 - 20 > ((i - (*ite_Bubble)->m_arrfx[0]))*40
		&& playerTwo.m_player_y + 20 - 20 < ((i + (*ite_Bubble)->m_arrfx[1]))*40 + 40)
		|| (playerTwo.m_player_x + 20 - 20 > (j - (*ite_Bubble)->m_arrfx[2])*40 
		&& playerTwo.m_player_x + 20 - 20 < (j + (*ite_Bubble)->m_arrfx[3])*40 + 40
		&& playerTwo.m_player_y + 20 - 20 > (i)*40
		&& playerTwo.m_player_y + 20 - 20 < (i)*40 + 40))
		return true;
	return false;
}

void CTwoGameScene::SetFx(list<CBubble*>::iterator &ite_Bubble, int i, int j) //�����ĸ�������ֵ
{
	for(int m = 0;m < 4;m++)
		(*ite_Bubble)->m_arrfx[m] = (*ite_Bubble)->m_nBubble_power;
	for(int n = 1;n <(*ite_Bubble)->m_nBubble_power + 1;n++)
	{
		if((gameMap.map_type[i - n][j] >= R_H_ && gameMap.map_type[i - n][j] <= WIND) || i - n < 0)
		{
			(*ite_Bubble)->m_arrfx[0] = n-1;
			break;
		}
	}
	for(int n = 1;n <(*ite_Bubble)->m_nBubble_power + 1;n++)
	{
		if((gameMap.map_type[i + n][j] >= R_H_ && gameMap.map_type[i + n][j] <= WIND) || i + n > MAP_HEIGHT - 1)
		{
			(*ite_Bubble)->m_arrfx[1] = n-1;
			break;
		}
	}
	for(int n = 1;n <(*ite_Bubble)->m_nBubble_power + 1;n++)
	{
		if((gameMap.map_type[i][j - n] >= R_H_ && gameMap.map_type[i][j - n] <= WIND) || j - n < 0)
		{
			(*ite_Bubble)->m_arrfx[2] = n-1;
			break;
		}
	}
	for(int n = 1;n <(*ite_Bubble)->m_nBubble_power + 1;n++)
	{
		if((gameMap.map_type[i][j + n] >= R_H_ && gameMap.map_type[i][j + n] <= WIND) || j + n > MAP_WIDTH - 1)
		{
			(*ite_Bubble)->m_arrfx[3] = n-1;
			break;
		}
	}
}

void CTwoGameScene::ChangeBoomShowID()
{
	list<CBubble*>::iterator ite_boom = m_lstBoom.begin();
	while(ite_boom != m_lstBoom.end())
	{
		if((*ite_boom)->m_nBoomShowID == 0)
		{
			delete (*ite_boom);
			ite_boom = m_lstBoom.erase(ite_boom);
		}else
		{
			(*ite_boom)->m_nBoomShowID--;
			++ite_boom;
		}
	}
}

void CTwoGameScene::AllBubbleShow(HDC hdc)
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		(*ite_Bubble)->BubbleShow(hdc);
		++ite_Bubble;
	}
}
void CTwoGameScene::AllBoomShow(HDC hdc)
{
	list<CBubble*>::iterator ite_Boom = m_lstBoom.begin();
	while(ite_Boom != m_lstBoom.end())
	{
		(*ite_Boom)->BoomShow(hdc);
		++ite_Boom;
	}
}
void CTwoGameScene::ShowTime(HDC hdc)
{
	// ʱ���ʽ00:00
	int time_one = 0; 
	int time_two = m_gameTime / 60;
	int time_three = (m_gameTime - time_two * 60) / 10;
	int time_four = (m_gameTime - time_two * 60) % 10;

	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,708,43,12,10,hdcMem,12*time_one,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,722,43,12,10,hdcMem,12*time_two,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,741,43,12,10,hdcMem,12*time_three,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,756,43,12,10,hdcMem,12*time_four,0,12,10,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ShowGameStatus(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	static int word_y = 0;
	// ƽ��!!!
	if (m_gameStatus == DRAW) word_y = 160; 
	// ��һ��� ʤ������
	else if (m_gameStatus == PLAYER_ONE_WIN) 
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,0,110,25,RGB(255,0,255));
	}
	// �ڶ���� ʤ������
	else if (m_gameStatus == PLAYER_TWO_WIN)
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,25,110,25,RGB(255,0,255));
	}
	// ��������ʾ
	else word_y = 0;

	// ѡ��������Ϣ
	SelectObject(hdcMem,m_bitmap_statusInfo);
	TransparentBlt(hdc,200,m_statusInfo_y,240,80,hdcMem,0,word_y,240,80,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ChangePlayerStartShowID()
{
	static int bflag = 0; // ���￪����˸����λ
	if (playerOne.m_Start_nShowID == 9 && playerTwo.m_Start_nShowID == 9)
	{

		playerOne.m_Start_nShowID = 8; //���1
		playerTwo.m_Start_nShowID = 8; //���2

		if (bflag == 4)
		{
			KillTimer(m_twoGameWnd,PLAYERSTART_TIMER_ID);
			bflag = 0;
			playerOne.m_player_status = MOVE;
			playerTwo.m_player_status = MOVE;
		}
		bflag++;
	}
	else
	{
		playerOne.m_Start_nShowID++;
		playerTwo.m_Start_nShowID++;
	}
}

//�ı���ߵ�ShowID
void CTwoGameScene::ChangePropShowID()
{
	if(prop.m_nShowID==0)
	{
		prop.m_nShowID=2;
	}
	else
	{
		prop.m_nShowID--;
	}
}
void CTwoGameScene::GameOver()
{
	// ���һʤ��
	if (playerOne.m_player_status == DIE)
	{
		m_gameStatus = PLAYER_TWO_WIN;
		playSound.Play(WIN_GAME_SOUND);
	}
	// ��Ҷ�ʤ��
	else if (playerTwo.m_player_status == DIE)
	{
		m_gameStatus = PLAYER_ONE_WIN;
		playSound.Play(WIN_GAME_SOUND);
	}
	// ƽ��
	else if(playerOne.m_player_status == DIE && playerTwo.m_player_status == DIE)
	{
		m_gameStatus = DRAW;
		playSound.Play(DRAW_GAME_SOUND);
	}

	m_statusInfo_y = 60;
	for(int i = TIMER_BEGIN;i <= TIMER_END;i++)
	{
		KillTimer(m_twoGameWnd ,i);
	}
}