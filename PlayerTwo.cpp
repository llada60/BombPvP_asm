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

	_asm
	{
		//SelectObject(hTempDC,m_hBmpPlayerShadow)
		mov         esi, esp
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 10h]
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x+12,m_player_y+53,32,15,hTempDC,0,0,32,15,RGB(255,0,255))
		push        0FF00FFh
		push        0Fh
		push        20h
		push        0
		push        0
		mov         eax, dword ptr[hTempDC]
		push        eax
		push        0Fh
		push        20h
		mov         ecx, dword ptr[this]
		mov         edx, dword ptr[ecx + 1Ch]
		add         edx, 35h
		push        edx
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		add         ecx, 0Ch
		push        ecx
		mov         edx, dword ptr[hdc]
		push        edx
		call        TransparentBlt

		//if (m_player_status == BEGIN)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 38h], 0
		jne         L1

		//SelectObject(hTempDC, m_hBmpPlayerStart)
		mov         eax, dword ptr[this]
		push        dword ptr[eax + 4]
		push		dword ptr[hTempDC]
		call		SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y,56,71,hTempDC,m_Start_nShowID*56,0,56,71,RGB(255,0,255))
		push        0FF00FFh
		push        47h
		push        38h
		push        0
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 14h], 38h
		push        ecx
		push        dword ptr[hTempDC]
		push        47h
		push        38h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		push        dword ptr[hdc]
		call        TransparentBlt
		jmp			end0

		//else if (m_player_status == MOVE)
		L1 :
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 38h], 1
		jne         L2

		//if (m_direction == UP)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 3Ch], 0
		jne         M1

		//SelectObject(hTempDC, m_hBmpPlayerMove)
		mov         eax, dword ptr[this]
		push        dword ptr[eax + 8]
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,UP*67,56,67,RGB(255,0,255))
		mov         esi, esp
		push        0FF00FFh
		push        43h
		push        38h
		push        0
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 38h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        43h
		push        38h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		mov         ecx, dword ptr[hdc]
		push        ecx
		call        TransparentBlt
		jmp         end0

		M1 :
		//else if (m_direction == DOWN)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 3Ch], 1
		jne         M2

		//SelectObject(hTempDC, m_hBmpPlayerMove)
		mov         esi, esp
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 8]
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,DOWN*67,56,67,RGB(255,0,255))
		mov         esi, esp
		push        0FF00FFh
		push        43h
		push        38h
		push        43h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 38h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        43h
		push        38h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		mov         ecx, dword ptr[hdc]
		push        ecx
		call        TransparentBlt
		jmp         end0

		M2 :
		//else if (m_direction == LEFT)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 3Ch], 2
		jne         M3

		//SelectObject(hTempDC, m_hBmpPlayerMove)
		mov         esi, esp
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 8]
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,LEFT*67,56,67,RGB(255,0,255))
		push        0FF00FFh
		push        43h
		push        38h
		push        86h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 38h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        43h
		push        38h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		mov         ecx, dword ptr[hdc]
		push        ecx
		call        TransparentBlt
		jmp         end0

		M3 :
		//else if (m_direction == RIGHT)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 3Ch], 3
		jne         end0

		//SelectObject(hTempDC, m_hBmpPlayerMove)
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 8]
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,m_Move_ShowId*56,RIGHT*67,56,67,RGB(255,0,255))
		push        0FF00FFh
		push        43h
		push        38h
		push        0C9h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 38h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        43h
		push        38h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		mov         ecx, dword ptr[hdc]
		push        ecx
		call        TransparentBlt
		jmp         end0

		L2 :
		//else if (m_player_status == DIE)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 38h], 2
		jne         end0

		//SelectObject(hTempDC, m_hBmpPlayerDie)
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 0Ch]
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc,m_player_x,m_player_y-34,56,98,hTempDC,(11-m_DieShowID)*56,0,56,98,RGB(255,0,255))
		push        0FF00FFh
		push        62h
		push        38h
		push        0
		mov         eax, dword ptr[this]
		mov         ecx, 0Bh
		sub         ecx, dword ptr[eax + 28h]
		imul        edx, ecx, 38h
		push        edx
		mov         eax, dword ptr[hTempDC]
		push        eax
		push        62h
		push        38h
		mov         ecx, dword ptr[this]
		mov         edx, dword ptr[ecx + 1Ch]
		sub         edx, 22h
		push        edx
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		push        ecx
		mov         edx, dword ptr[hdc]
		push        edx
		call        TransparentBlt

		end0 :
		//DeleteObject(hTempDC)
		mov         eax, dword ptr[hTempDC]
		push        eax
		call        DeleteObject
	}

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
		add         ecx, 37h
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

	int temp_x;
	int temp_y;
	CBubble* bubble = new CBubble;

	_asm
	{
		mov         eax, dword ptr[x]
		add         eax, 0Fh
		mov         dword ptr[x], eax

		mov         eax, dword ptr[y]
		add         eax, 40h
		mov         dword ptr[y], eax

		cmp         dword ptr[x], 14h
		jl          end0
		cmp         dword ptr[x], 26Ch
		jg          end0
		cmp         dword ptr[y], 29h
		jl          end0
		cmp         dword ptr[y], 231h
		jg          end0

		mov         eax, dword ptr[x]
		sub         eax, 14h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_x], eax

		mov         eax,dword ptr [y]
		sub         eax,29h
		cdq
		mov         ecx,28h
		idiv        ecx
		mov         dword ptr [temp_y],eax

		imul        eax,dword ptr [temp_y],3Ch
		add         eax,dword ptr [gameMap]
		mov         ecx,dword ptr [temp_x]
		cmp         dword ptr [eax+ecx*4],0
		jne         end0

		imul        eax,dword ptr [temp_y],3Ch
		add         eax,dword ptr [gameMap]
		mov         ecx,dword ptr [temp_x]
		mov         dword ptr [eax+ecx*4],9

		imul        eax,dword ptr [temp_x],28h
		add         eax,14h
		mov         dword ptr [temp_x],eax

		imul        eax,dword ptr [temp_y],28h
		add         eax,28h
		mov         dword ptr [temp_y],eax

		mov         eax,dword ptr [this]
		mov         ecx,dword ptr [eax+34h]
		push        ecx
		mov         edx,dword ptr [temp_y]
		push        edx
		mov         eax,dword ptr [temp_x]
		push        eax
		mov         ecx,dword ptr [hIns]
		push        ecx
		mov         ecx,dword ptr [bubble]
		call        CBubble::BubbleInit

		//bubble->m_bubble_owner = OWNER_PLAYERTWO;
		mov         eax, dword ptr[bubble]
		mov         dword ptr [eax+28h],2
	end0:
	}
	lstBubble.push_back(bubble);

	// 放置泡泡音效
	playSound.Play(PUT_BUEBLE_SOUND);

	/*
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
	}*/
}

bool CPlayerTwo::WhetherProp(CGameProps &gameprop)
{
	int x_temp, y_temp;
	bool flag;
	_asm {
		// 将坐标转换成对应地图数组坐标
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
		// 判断是否吃到道具
		// bool flag = false; 
		mov         byte ptr[flag], 0
		// switch (gameprop.m_bj[y_temp][x_temp])
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         ecx, dword ptr[edx + eax * 4]
		sub			ecx, 0Ah
		// 跳转到各个分支
		cmp			ecx, 0
		je			Noprop
		cmp			ecx, 1
		je			Energybubble
		cmp			ecx, 2
		je			Energywater
		cmp			ecx, 3
		je			Rollerskate
		cmp			ecx, 4
		je			Redhead
		cmp			ecx, 5
		je			Powerball
		jmp			Done
Noprop :
// 没有道具 case noprop:
// flag = false;
		mov         byte ptr[flag], 0
		jmp         Done
Energybubble :
//	水泡，吃一个可以多放一个水泡 case energybubble:
//	gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		//	if (m_bubbleNum < _DEF_BUBBLE_NUM_MAX)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 30h], _DEF_BUBBLE_NUM_MAX
		jge         GreaterEnergybubble
		// 改变放置泡泡个数
		//	m_bubbleNum++;
		mov         ecx, dword ptr[eax + 30h]
		add         ecx, 1
		mov         dword ptr[eax + 30h], ecx
GreaterEnergybubble:
		//flag = true;
		mov         byte ptr[flag], 1
		jmp         Done
Energywater :
// 能量水，吃了水泡的威力增加一倍 case energywater:
// gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		// 改变泡泡的威力
		//if (m_bubblePower < _DEF_BUBBLE_POWER_MAX)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 34h], _DEF_BUBBLE_POWER_MAX
		jge         GreaterEnergywater
		//	m_bubblePower++;
		mov         ecx, dword ptr[eax + 34h]
		add         ecx, 1
		mov         dword ptr[eax + 34h], ecx
GreaterEnergywater :
		//flag = true;
		mov         byte ptr[flag], 1
		jmp         Done
Rollerskate :
// 旱冰鞋，增加人物移动速度 case rollerskate:
//gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		// 改变移动速度
		//if (m_speed_timer > 10)
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 2Ch], 0Ah
		jle			LessRollerskate
		//m_speed_timer -= 10;
		mov         ecx, dword ptr[eax + 2Ch]
		sub         ecx, 0Ah
		mov         dword ptr[eax + 2Ch], ecx
LessRollerskate :
		//flag = true;
		mov         byte ptr[flag], 1
		jmp         Done
Redhead :
// 红魔头，速度达到最大值 case redhead:
// gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		//m_speed_timer = 10;
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 2Ch], 0Ah
		jmp         Done
Powerball :
// 大力丸，水泡威力达到最大值 case powerball:
// gameprop.m_bj[y_temp][x_temp] = noprop;
		imul        eax, dword ptr[y_temp], 34h
		mov         ecx, dword ptr[gameprop]
		lea         edx, [ecx + eax + 18h]
		mov         eax, dword ptr[x_temp]
		mov         dword ptr[edx + eax * 4], 0Ah
		// 泡泡威力为最大值
		//m_bubblePower = _DEF_BUBBLE_POWER_MAX;
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 34h], _DEF_BUBBLE_POWER_MAX
		//flag = true;
		mov         byte ptr[flag], 1
Done:
		//if (flag)
		movzx       eax, byte ptr[flag]
		test        eax, eax
		je          True
		mov         al, 1
		jmp         False
True :
		xor al, al
False :
	}
}
