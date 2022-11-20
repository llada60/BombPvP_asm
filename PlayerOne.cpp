#include "PlayerOne.h"

CPlayerOne::CPlayerOne()
{
}

CPlayerOne::~CPlayerOne()
{
} 

void CPlayerOne::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 15;     // 图片宽480 高64 -->  每个人物宽48
	m_player_y = 15;
	m_Start_nShowID = 0;
	m_DieShowID = 11;
	m_speed_timer = _DEF_PLAYER_SPEED_TIMER;
	m_bubbleNum = 1;
	m_bubblePower = 1;
	m_player_status = BEGIN;
	m_direction = DOWN;
	m_hBmpPlayerStart = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
	m_hBmpPlayerMove = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_MOVE));
	m_hBmpPlayerDie = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_DIE));

}

void CPlayerOne::PlayerShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);

	// 人物阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow); 
	TransparentBlt(hdc,m_player_x+8,m_player_y+48,32,15,hTempDC,0,0,32,15,RGB(255,0,255));

	switch (m_player_status)
	{
	// 开场动画
	case BEGIN:
		SelectObject(hTempDC,m_hBmpPlayerStart);
		TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Start_nShowID*48,0,48,64,RGB(255,0,255));
		break;

	// 移动动画
	case MOVE:
		switch (m_direction)
		{
		case UP:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,UP*64,48,64,RGB(255,0,255));
			break;
		case DOWN:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,DOWN*64,48,64,RGB(255,0,255));
			break;
		case LEFT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,LEFT*64,48,64,RGB(255,0,255));
			break;
		case RIGHT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,RIGHT*64,48,64,RGB(255,0,255));
			break;
		}
		break;

	// 死亡动画
	case DIE:
			SelectObject(hTempDC,m_hBmpPlayerDie);
			TransparentBlt(hdc,m_player_x,m_player_y-36,48,100,hTempDC,(11-m_DieShowID)*48,0,48,100,RGB(255,0,255));
		break;
	}

	DeleteObject(hTempDC);
}

void CPlayerOne::PlayerMove(int FX,CGameMap &gameMap,CGameProps &gameprop,CPlaySound &playSound)
{
	// 根据人物位图下中坐标判断是否有障碍物
	// 将坐标转换成对应地图数组坐标
	int temp_x = (m_player_x - 20 + 24) / 40;
	int temp_y = (m_player_y + 64 - 41) / 40;
	// 定义人物位图位置 与障碍物位置比较 看人物是否可以移动
	int nPicture_x = 0;
	int nPicture_y = 0;
	int nBlock_x = 0;
	int nBlock_y = 0;
	// 移动
	if (FX == 'A')
	{
		m_direction = LEFT;
		nPicture_x = m_player_x;                   // 人物位图最左侧位置
		nBlock_x = (temp_x - 1) * 40 + 20 + 40;    // 障碍物右侧位置
		if (this->m_player_x +3 > 15 && 
			!(gameMap.map_type[temp_y][temp_x - 1] != No && nPicture_x  <= nBlock_x))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_x -= 5;
		}
	}

	if (FX == 'D')
	{
		m_direction = RIGHT;
		nPicture_x = m_player_x + 48;           // 人物位图最右侧位置
		nBlock_x = (temp_x + 1) * 40 + 20;      // 障碍物左侧位置
		if (this->m_player_x +3 < 20 + 600 - 48 && 
			!(gameMap.map_type[temp_y][temp_x + 1] != No && nPicture_x  >= nBlock_x))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_x += 5;
		}
	}

	if (FX == 'W')
	{
		m_direction = UP;
		nPicture_y = m_player_y + 32;                // 人物位图最上方位置
		nBlock_y = (temp_y - 1) * 40 + 40 + 40;      // 障碍物下方位置
		if (this->m_player_y +3> 15 && 
			!(gameMap.map_type[temp_y - 1][temp_x] != No && nPicture_y  <= nBlock_y))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_y -= 5;
		}
	}

	if (FX == 'S')
	{
		m_direction = DOWN;
		nPicture_y = m_player_y + 68;           // 人物位图最下方位置
		nBlock_y = (temp_y + 1) * 40 + 40;      // 障碍物上方位置
		if (this->m_player_y +3 < 41 + 520 - 64 && 
			!(gameMap.map_type[temp_y + 1][temp_x] != No && nPicture_y  >= nBlock_y))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_y += 5;
		}
	}
}

void CPlayerOne::CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y)
{
	//-------坐标转换-------------------//
	x += 15;
	y = y + 64 - 15;

	if (x >= 20 && x <= 620 && y >= 41 && y <= 561)
	{
		// 将坐标转换成对应地图数组坐标
		int temp_x = (x - 20) / 40; 
		int temp_y = (y - 41) / 40;
		// 判断该位置是否有障碍物 没有障碍物 允许放泡泡
		if (gameMap.map_type[temp_y][temp_x] == No)
		{
			// 将该位置赋值
			gameMap.map_type[temp_y][temp_x] = Popo;
			// 确定泡泡位置
			temp_x = temp_x * 40 + 20;
			temp_y = temp_y * 40 + 41 - 1;
			// 创建泡泡
			CBubble* bubble = new CBubble;
			bubble->BubbleInit(hIns,temp_x,temp_y,m_bubblePower);
			bubble->m_bubble_owner = OWNER_PLAYERONE;
			lstBubble.push_back(bubble);

			// 放置泡泡音效
			playSound.Play(PUT_BUEBLE_SOUND);
		}
	}
}

bool CPlayerOne::WhetherProp(CGameProps &gameprop)
{
	// 将坐标转换成对应地图数组坐标
	int x_temp = (m_player_x - 20 + 24) / 40;
	int y_temp = (m_player_y + 64 - 41) / 40;
	bool flag = false; // 判断是否吃到道具
	switch (gameprop.m_bj[y_temp][x_temp])
	{
	case noprop:
		flag = false;
		break;
	case energybubble:
		{
			gameprop.m_bj[y_temp][x_temp] = noprop;
			// 改变放置泡泡个数
			if (m_bubbleNum < _DEF_BUBBLE_NUM_MAX)
			{
				m_bubbleNum++;
			}
			flag = true;
		}
		break;
	case energywater:
		{
			gameprop.m_bj[y_temp][x_temp] = noprop;
			// 改变泡泡的威力
			if (m_bubblePower < _DEF_BUBBLE_POWER_MAX)
			{
				m_bubblePower++;
			}
			flag = true;
		}
		break;
	case rollerskate:
		{
			gameprop.m_bj[y_temp][x_temp] = noprop;
			// 改变移动速度
			if (m_speed_timer > 10)
			{
				m_speed_timer -= 10;
			}
			flag = true;
		}
		break;
	case redhead:
		{
			gameprop.m_bj[y_temp][x_temp] = noprop;
			m_speed_timer = 10;
		}
		break;
	case powerball:
		{
			gameprop.m_bj[y_temp][x_temp] = noprop;
			// 泡泡威力为最大值
			m_bubblePower = _DEF_BUBBLE_POWER_MAX;
			flag = true;
		}
		break;
	}

	if (flag)
	{
		return true;
	}
	return false;
}