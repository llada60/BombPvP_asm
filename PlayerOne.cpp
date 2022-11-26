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
	int x_temp, y_temp;
	bool flag;
	_asm {
		// int x_temp = (m_player_x - 20 + 24) / 40;
		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 18h]
		add         eax, 4
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[x_temp], eax
		// int y_temp = (m_player_y + 64 - 41) / 40;
		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 1Ch]
		add         eax, 17h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[y_temp], eax
		// bool flag = false; // 判断是否吃到道具
		mov         byte ptr[flag], 0
		// switch (gameprop.m_bj[y_temp][x_temp])
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         ecx, dword ptr[edx + eax * 4]
		mov         dword ptr[ebp - 0F4h], ecx
		mov         edx, dword ptr[ebp - 0F4h]
		sub         edx, 0Ah
		mov         dword ptr[ebp - 0F4h], edx
		cmp         dword ptr[ebp - 0F4h], 5
		ja          Done
		mov         eax, dword ptr[ebp - 0F4h]
		//s		jmp         dword ptr[eax * 4 + 23B744h]
		cmp			eax, 0
		je			Noprop
		cmp			eax, 1
		je			Energybubble
		cmp			eax, 2
		je			Energywater
		cmp			eax, 3
		je			Rollerskate
		cmp			eax, 4
		je			Redhead
		cmp			eax, 5
		je			Powerball
	Noprop:
		// 	case noprop:
		// flag = false;
		mov         byte ptr[flag], 0
		jmp         Done// break;
	Energybubble:
		//	case energybubble:
		//{
		//	gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		//			if (m_bubbleNum < _DEF_BUBBLE_NUM_MAX)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 30h], 5
		jge         CPlayerOne::WhetherProp + 0CCh
		//{
		//	m_bubbleNum++;
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 30h]
		add         ecx, 1
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 30h], ecx
		//}
		//flag = true;
		mov         byte ptr[flag], 1
		//}
		//break;
		jmp         Done
	Energywater:
		//case energywater:
		///	{
		//		gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		// �ı����ݵ�����
		//if (m_bubblePower < _DEF_BUBBLE_POWER_MAX)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 34h], 4
		jge         CPlayerOne::WhetherProp + 102h
		//{
		//	m_bubblePower++;
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 34h]
		add         ecx, 1
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 34h], ecx
		//}
		//flag = true;
		mov         byte ptr[flag], 1
		//}
		//break;
		jmp         Done
	Rollerskate:
		//case rollerskate:
			//{
				//gameprop.m_bj[y_temp][x_temp] = noprop;
				imul        eax, dword ptr[y_temp], 34h
				mov         ecx, dword ptr[gameprop]
				lea         edx, [ecx + eax + 18h]
				mov         eax, dword ptr[x_temp]
				mov         dword ptr[edx + eax * 4], 0Ah
				// �ı��ƶ��ٶ�
				//if (m_speed_timer > 10)
				mov         eax, dword ptr[this]
				cmp         dword ptr[eax + 2Ch], 0Ah
				jle         CPlayerOne::WhetherProp + 135h
				//{
					//m_speed_timer -= 10;
					mov         eax, dword ptr[this]
					mov         ecx, dword ptr[eax + 2Ch]
					sub         ecx, 0Ah
					mov         edx, dword ptr[this]
					mov         dword ptr[edx + 2Ch], ecx
					//}
					//flag = true;
					mov         byte ptr[flag], 1
					//}
					//break;
					jmp         Done
	Redhead:
	//case redhead:
	//{
		//gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		//m_speed_timer = 10;
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 2Ch], 0Ah
		//}
		//break;
		jmp         Done
	Powerball:
		//case powerball:
		//{
		//gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		// ��������Ϊ���ֵ
		//m_bubblePower = _DEF_BUBBLE_POWER_MAX;
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 34h], 4
		//flag = true;
		mov         byte ptr[flag], 1
		//}
		//break;
	//}
		Done:
		//if (flag)
		movzx       eax, byte ptr[flag]
		test        eax, eax
		je          True
		//{
			//return true;
		mov         al, 1
		jmp         False
		//}
		//return false;
		True :
		xor al, al
	//}
	False :
		pop         edi
		pop         esi
		pop         ebx
		add         esp, 0F4h
		cmp         ebp, esp
		//call        __RTC_CheckEsp 
		mov         esp, ebp
		pop         ebp
		ret         4
		nop
		mov         dh, 23h
		add         byte ptr[edi], bh
		mov         dh, 23h
		add         byte ptr[ebp - 4Ah], dh
		and eax, dword ptr[eax]
		test        al, 0B6h
		and eax, dword ptr[eax]
	}
}
