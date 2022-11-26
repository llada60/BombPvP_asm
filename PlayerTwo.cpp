#include "PlayerTwo.h"

CPlayerTwo::CPlayerTwo()
{
}

CPlayerTwo::~CPlayerTwo()
{
} 
void CPlayerTwo::PlayerInit(HINSTANCE hIns)
{
	_asm {
		mov eax, dword ptr[this]
		mov dword ptr[eax + 18h], 575
		mov dword ptr[eax + 1Ch], 494
		mov dword ptr[eax + 14h], 0
		mov dword ptr[eax + 28h], 0Bh
		mov dword ptr[eax + 2Ch], 28h
		mov dword ptr[eax + 30h], 1
		mov dword ptr[eax + 34h], 1
		mov dword ptr[eax + 38h], 0
		mov dword ptr[eax + 3Ch], 1
	}
	/*m_player_x = 575;	// 图片宽560 高71 每个人物宽56,
	m_player_y = 494;
	m_Start_nShowID = 0;
	m_DieShowID = 11;
	m_speed_timer = _DEF_PLAYER_SPEED_TIMER;
	m_player_status = BEGIN;
	m_direction = DOWN;
	m_bubblePower = 1;*/
	m_hBmpPlayerStart = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
	m_hBmpPlayerMove = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_MOVE));
	m_hBmpPlayerDie = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_DIE));
}

void CPlayerTwo::PlayerShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);
	// 阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow);
	TransparentBlt(hdc,m_player_x+12,m_player_y+53,32,15,hTempDC,0,0,32,15,RGB(255,0,255));

	switch (m_player_status)
	{
	// 开场动画
	case BEGIN:
		SelectObject(hTempDC,m_hBmpPlayerStart);
		TransparentBlt(hdc,m_player_x,m_player_y,56,71,hTempDC,m_Start_nShowID*56,0,56,71,RGB(255,0,255));
		break;

	// 移动动画
	case MOVE:
		switch (m_direction)
		{
		case UP:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,UP*67,56,67,RGB(255,0,255));
			break;
		case DOWN:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,DOWN*67,56,67,RGB(255,0,255));
			break;
		case LEFT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,LEFT*67,56,67,RGB(255,0,255));
			break;
		case RIGHT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,RIGHT*67,56,67,RGB(255,0,255));
			break;
		}
		break;

	// 死亡动画
	case DIE:
		SelectObject(hTempDC,m_hBmpPlayerDie);
		TransparentBlt(hdc,m_player_x,m_player_y-34,56,98,hTempDC,(11-m_DieShowID)*56,0,56,98,RGB(255,0,255));
		break;
	}

	DeleteObject(hTempDC);
}

void CPlayerTwo::PlayerMove(int FX,CGameMap &gameMap,CGameProps &gameprop,CPlaySound &playSound)
{
	/*// 根据人物位图下中坐标判断是否有障碍物
	// 将坐标转换成对应地图数组坐标
	int temp_x = (m_player_x - 20 + 24) / 40;
	int temp_y = (m_player_y + 64 - 41) / 40;
	// 定义人物位图位置 与障碍物位置比较 看人物是否可以移动
	int nPicture_x = 0;
	int nPicture_y = 0;
	int nBlock_x = 0;
	int nBlock_y = 0;*/


	// 根据人物位图下中坐标判断是否有障碍物
	// 将坐标转换成对应地图数组坐标
	int temp_x;
	int temp_y;
	// 定义人物位图位置 与障碍物位置比较 看人物是否可以移动
	int nPicture_x;
	int nPicture_y;
	int nBlock_x;
	int nBlock_y;


	_asm {
		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 18h]
		add         eax, 4
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_x], eax

		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 1Ch]
		add         eax, 17h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_y], eax

		mov         dword ptr[nPicture_x], 0
		mov         dword ptr[nPicture_y], 0
		mov         dword ptr[nBlock_x], 0
		mov         dword ptr[nBlock_y], 0

		cmp         dword ptr[FX], VK_LEFT
		jne         LA2

		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 3Ch], 2

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		mov         dword ptr[nPicture_x], ecx

		mov         eax, dword ptr[temp_x]
		sub         eax, 1
		imul        ecx, eax, 28h
		add         ecx, 3Ch
		mov         dword ptr[nBlock_x], ecx

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		add         ecx, 3
		cmp         ecx, 0Fh
		jle         LA2
		imul        eax, dword ptr[temp_y], 3Ch
		add         eax, dword ptr[gameMap]
		mov         ecx, dword ptr[temp_x]
		cmp         dword ptr[eax + ecx * 4 - 4], 0
		je          LA1
		mov         eax, dword ptr[nPicture_x]
		cmp         eax, dword ptr[nBlock_x]
		jle         LA2

		LA1 :
		mov         esi, esp
			mov         eax, dword ptr[gameprop]
			push        eax
			mov         ecx, dword ptr[this]
			mov         edx, dword ptr[ecx]
			mov         ecx, dword ptr[this]
			mov         eax, dword ptr[edx + 14h]
			call        eax

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 18h]
			sub         ecx, 5
			mov         edx, dword ptr[this]
			mov         dword ptr[edx + 18h], ecx

			LA2 :
		cmp         dword ptr[FX], VK_RIGHT
			jne			LD2
			mov         eax, dword ptr[this]
			mov         dword ptr[eax + 3Ch], 3

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 18h]
			add         ecx, 30h
			mov         dword ptr[nPicture_x], ecx

			mov         eax, dword ptr[temp_x]
			add         eax, 1
			imul        ecx, eax, 28h
			add         ecx, 14h
			mov         dword ptr[nBlock_x], ecx

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 18h]
			add         ecx, 3
			cmp         ecx, 23Ch
			jge         LD2
			imul        eax, dword ptr[temp_y], 3Ch
			add         eax, dword ptr[gameMap]
			mov         ecx, dword ptr[temp_x]
			cmp         dword ptr[eax + ecx * 4 + 4], 0
			je          LD1
			mov         eax, dword ptr[nPicture_x]
			cmp         eax, dword ptr[nBlock_x]
			jge         LD2
			LD1 :
		mov         esi, esp
			mov         eax, dword ptr[gameprop]
			push        eax
			mov         ecx, dword ptr[this]
			mov         edx, dword ptr[ecx]
			mov         ecx, dword ptr[this]
			mov         eax, dword ptr[edx + 14h]
			call        eax

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 18h]
			add         ecx, 5
			mov         edx, dword ptr[this]
			mov         dword ptr[edx + 18h], ecx

			LD2 :
		cmp         dword ptr[FX], VK_UP
			jne			LW2

			mov         eax, dword ptr[this]
			mov         dword ptr[eax + 3Ch], 0

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			add         ecx, 20h
			mov         dword ptr[nPicture_y], ecx

			mov         eax, dword ptr[temp_y]
			sub         eax, 1
			imul        ecx, eax, 28h
			add         ecx, 50h
			mov         dword ptr[nBlock_y], ecx

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			add         ecx, 3
			cmp         ecx, 0Fh
			jle         LW2
			mov         eax, dword ptr[temp_y]
			sub         eax, 1
			imul        ecx, eax, 3Ch
			add         ecx, dword ptr[gameMap]
			mov         edx, dword ptr[temp_x]
			cmp         dword ptr[ecx + edx * 4], 0
			je          LW1
			mov         eax, dword ptr[nPicture_y]
			cmp         eax, dword ptr[nBlock_y]
			jle         LW2
			LW1 :
		mov         esi, esp
			mov         eax, dword ptr[gameprop]
			push        eax
			mov         ecx, dword ptr[this]
			mov         edx, dword ptr[ecx]
			mov         ecx, dword ptr[this]
			mov         eax, dword ptr[edx + 14h]
			call        eax

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			sub         ecx, 5
			mov         edx, dword ptr[this]
			mov         dword ptr[edx + 1Ch], ecx

			LW2 :
		cmp         dword ptr[FX], VK_DOWN
			jne         LS2

			mov         eax, dword ptr[this]
			mov         dword ptr[eax + 3Ch], 1

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			add         ecx, 44h
			mov         dword ptr[nPicture_y], ecx

			mov         eax, dword ptr[temp_y]
			add         eax, 1
			imul        ecx, eax, 28h
			add         ecx, 28h
			mov         dword ptr[nBlock_y], ecx

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			add         ecx, 3
			cmp         ecx, 1F1h
			jge         LS2
			mov         eax, dword ptr[temp_y]
			add         eax, 1
			imul        ecx, eax, 3Ch
			add         ecx, dword ptr[gameMap]
			mov         edx, dword ptr[temp_x]
			cmp         dword ptr[ecx + edx * 4], 0
			je          LS1
			mov         eax, dword ptr[nPicture_y]
			cmp         eax, dword ptr[nBlock_y]
			jge         LS2
			LS1 :
		mov         esi, esp
			mov         eax, dword ptr[gameprop]
			push        eax
			mov         ecx, dword ptr[this]
			mov         edx, dword ptr[ecx]
			mov         ecx, dword ptr[this]
			mov         eax, dword ptr[edx + 14h]
			call        eax

			mov         eax, dword ptr[this]
			mov         ecx, dword ptr[eax + 1Ch]
			add         ecx, 5
			mov         edx, dword ptr[this]
			mov         dword ptr[edx + 1Ch], ecx
			LS2 :
	}
	// 移动
	/*if (FX == VK_LEFT)
	{
		m_direction = LEFT;
		nPicture_x = m_player_x;                   // 人物位图最左侧位置
		nBlock_x = (temp_x - 1) * 40 + 20 + 35;    // 障碍物右侧位置
		if (this->m_player_x > 15 && 
			!(gameMap.map_type[temp_y][temp_x - 1] != No && nPicture_x <= nBlock_x))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_x -= 5;
		}
	}

	if (FX == VK_RIGHT)
	{
		m_direction = RIGHT;
		nPicture_x = m_player_x + 48;           // 人物位图最右侧位置
		nBlock_x = (temp_x + 1) * 40 + 20;      // 障碍物左侧位置
		if (this->m_player_x < 575 && 
			!(gameMap.map_type[temp_y][temp_x + 1] != No && nPicture_x >= nBlock_x))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_x += 5;
		}
	}

	if (FX == VK_UP)
	{
		m_direction = UP;
		nPicture_y = m_player_y + 32;                // 人物位图最上方位置
		nBlock_y = (temp_y - 1) * 40 + 40 + 40;      // 障碍物下方位置
		if (this->m_player_y > 15 && 
			!(gameMap.map_type[temp_y - 1][temp_x] != No && nPicture_y <= nBlock_y))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_y -= 5;
		}
	}

	if (FX == VK_DOWN)
	{
		m_direction = DOWN;
		nPicture_y = m_player_y + 75;           // 人物位图最下方位置
		nBlock_y = (temp_y + 1) * 40 + 40;      // 障碍物上方位置
		if (this->m_player_y < 41 + 520 - 67 && 
			!(gameMap.map_type[temp_y + 1][temp_x] != No && nPicture_y >= nBlock_y))
		{
			if (this->WhetherProp(gameprop))
			{
				playSound.Play(GET_TOOL_SOUND);
			}
			this->m_player_y += 5;
		}
	}*/
}

void CPlayerTwo::CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y)
{
	//-------坐标转换-------------------//
	x = x + 15;
	y = y + 64;

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
			bubble->m_bubble_owner = OWNER_PLAYERTWO;
			lstBubble.push_back(bubble);

			// 放置泡泡音效
			playSound.Play(PUT_BUEBLE_SOUND);
		}
	}
}

bool CPlayerTwo::WhetherProp(CGameProps &gameprop)
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
		Noprop :
		// 	case noprop:
		// flag = false;
		mov         byte ptr[flag], 0
			jmp         Done// break;
			Energybubble :
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
			jge         CPlayerTwo::WhetherProp + 0CCh
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
			Energywater :
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
			jge         CPlayerTwo::WhetherProp + 102h
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
			Rollerskate :
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
			jle         CPlayerTwo::WhetherProp + 135h
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
			Redhead :
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
			Powerball :
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