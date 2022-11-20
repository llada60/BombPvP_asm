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

	m_gameTime = 300;      // 倒计时计数器 300s
	m_statusInfo_y = 70;   // 文字默认位置 y = 70
	m_gameStatus = START;  // 游戏开始 显示游戏开始文字

	// 初始化地图
	gameMap.MapInit(hIns);

	//初始化道具
	prop.PropInit(hIns,gameMap);

	// 初始化游戏人物
	playerOne.PlayerInit(hIns);
	playerTwo.PlayerInit(hIns);

	// 启动定时器
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
	// 游戏开始音效
	playSound.Play(START_GAME_SOUND);
}

void CTwoGameScene::TwoGameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
	SelectObject(hdcMem,m_bitmap_road);
	BitBlt(hdc,20,41,600,520,hdcMem,0,0,SRCCOPY);

	// 退出按钮
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

	// 泡泡显示
	this->AllBubbleShow(hdc);
	// 爆炸泡泡显示
	this->AllBoomShow(hdc);

	//道具显示
	prop.PropPositionShow(hdc);

	// 地图显示
	gameMap.MapShow(hdc);

	// 倒计时
	this->ShowTime(hdc);

	//人物出场显示
	playerOne.PlayerShow(hdc);
	playerTwo.PlayerShow(hdc);

	gameMap.MapUpShow(hdc);
	// 正常游戏过程中不调用该函数，只要游戏开始结束时启动定时器不断调用
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
	// 关闭音效
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
	// 玩家一放置泡泡
	case  VK_SPACE:
		// 遍历链表 看玩家一已放置的泡泡
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
	// 玩家二放置泡泡
	case VK_SHIFT:
		{
			// 遍历链表 看玩家二已放置的泡泡
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
		// 人物一移动
	
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		{
			// 将移动标记置为true
			playerOne.m_bMoveFlag = true;

		}
		break;
		// 人物二移动
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		{
			// 将移动标记置为true
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
	// 停止音效
	if (nTimerID == STOPSOUND_TIMER_ID)
	{
		if (playSound.isPlay && (playSound.GetPos() >= playSound.GetFileLen()))
		{
			playSound.Stop();
		}
	}

	// 泡泡跳动动画定时器
	if (nTimerID == BUBBLE_CHANGE_TIMER_ID)
	{

		this->ChangeBubbleShowID();

	}
	if (nTimerID == PROPERTY_BOOM_TIMER_ID)
	{

		this->ChangeBoomShowID();

	}

	// 改变倒计时计数器--
	if (nTimerID == GAME_TIME_TIMER_ID)
	{
		if (m_gameTime == 0)
		{
			// 弹出平局文字
			m_gameStatus = DRAW;
			m_statusInfo_y = 60;

			// 播放平局音效
			playSound.Play(DRAW_GAME_SOUND);

			// 关闭所有定时器
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

	// 改变文字位置
	if (nTimerID == STATUS_INFO_TIMER_ID)
	{
		if (m_statusInfo_y <= -80)
		{
			KillTimer(m_twoGameWnd,STATUS_INFO_TIMER_ID); // 停止计时器
			m_gameStatus = NO_SHOW;                       // 将游戏文字状态标记置为默认
		}
		else
		{
			m_statusInfo_y -= 20;
		}
	}

	// 玩家出场动画定时器
	if (nTimerID == PLAYERSTART_TIMER_ID)
	{
		this->ChangePlayerStartShowID();
	}

	// 风车转定时器
	if (nTimerID == WIND_TIMER_ID)
	{
		if(gameMap.m_nShowID == 1) gameMap.m_nShowID = 0;
		else gameMap.m_nShowID = 1;
	}

	// 人物移动定时器
	if (nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		// 通过改变监测按键时间 改变移动速度
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
	// 人物移动动画定时器
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
	// 道具变化定时器
	if(nTimerID == PROPERTY_CHANGR_TIMER_ID)
	{
		this->ChangePropShowID();
	}
	// 玩家死亡
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
	// 按键按下出泡泡，鼠标传入对应的点x,y
	//	this->CreateBubble(hIns, point.x, point.y);
}

void CTwoGameScene::ChangeBubbleShowID()
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		// 判断跳动到第几次，五次后消失
		if((*ite_Bubble)->m_nBubbleBj == 0)
		{
			// 将坐标转换成对应数组下标
			int i = ((*ite_Bubble)->m_nBubble_y - 40) / 40;
			int j = ((*ite_Bubble)->m_nBubble_x - 20) / 40;
			// 消除地图障碍物
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
			// 将地图该位置置为空 即 No
			gameMap.map_type[i][j] = No;
			// 删除该泡泡
			m_lstBoom.push_back(*ite_Bubble);
			ite_Bubble = m_lstBubble.erase(ite_Bubble);

			playSound.Play(BLAST_SOUND); // 爆炸音效
		}
		else
		{
			//改变泡泡的showid实现它的跳动变换
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

void CTwoGameScene::SetFx(list<CBubble*>::iterator &ite_Bubble, int i, int j) //设置四个方向数值
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
	// 时间格式00:00
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
	// 平局!!!
	if (m_gameStatus == DRAW) word_y = 160; 
	// 第一玩家 胜利！！
	else if (m_gameStatus == PLAYER_ONE_WIN) 
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,0,110,25,RGB(255,0,255));
	}
	// 第二玩家 胜利！！
	else if (m_gameStatus == PLAYER_TWO_WIN)
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,25,110,25,RGB(255,0,255));
	}
	// 无文字提示
	else word_y = 0;

	// 选择文字信息
	SelectObject(hdcMem,m_bitmap_statusInfo);
	TransparentBlt(hdc,200,m_statusInfo_y,240,80,hdcMem,0,word_y,240,80,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ChangePlayerStartShowID()
{
	static int bflag = 0; // 人物开场闪烁控制位
	if (playerOne.m_Start_nShowID == 9 && playerTwo.m_Start_nShowID == 9)
	{

		playerOne.m_Start_nShowID = 8; //玩家1
		playerTwo.m_Start_nShowID = 8; //玩家2

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

//改变道具的ShowID
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
	// 玩家一胜利
	if (playerOne.m_player_status == DIE)
	{
		m_gameStatus = PLAYER_TWO_WIN;
		playSound.Play(WIN_GAME_SOUND);
	}
	// 玩家二胜利
	else if (playerTwo.m_player_status == DIE)
	{
		m_gameStatus = PLAYER_ONE_WIN;
		playSound.Play(WIN_GAME_SOUND);
	}
	// 平局
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