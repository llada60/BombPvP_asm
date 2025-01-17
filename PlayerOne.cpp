#include "PlayerOne.h"
CPlayerOne::CPlayerOne()
{
}

CPlayerOne::~CPlayerOne()
{
}

void CPlayerOne::PlayerInit(HINSTANCE hIns)
{
	//人物属性初始化
	_asm {
		mov eax, dword ptr[this]
		mov dword ptr[eax + 18h], 0Fh
		mov dword ptr[eax + 1Ch], 0Fh
		mov dword ptr[eax + 14h], 0
		mov dword ptr[eax + 28h], 0Bh
		mov dword ptr[eax + 2Ch], 28h
		mov dword ptr[eax + 30h], 1
		mov dword ptr[eax + 34h], 1
		mov dword ptr[eax + 38h], 0
		mov dword ptr[eax + 3Ch], 1
	}
	//加载对应动作的位图
	m_hBmpPlayerStart = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYER_ONE_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SHADOW_ROLE));
	m_hBmpPlayerMove = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYER_ONE_MOVE));
	m_hBmpPlayerDie = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_PLAYER_ONE_DIE));

}

//人物的动画
void CPlayerOne::PlayerShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);


	_asm
	{
		// 人物阴影
		//SelectObject(hTempDC,m_hBmpPlayerShadow);
		mov eax, dword ptr[this]
		push dword ptr[eax + 10h]
		push dword ptr[hTempDC]
		call SelectObject

		//TransparentBlt(hdc,m_player_x+8,m_player_y+48,32,15,hTempDC,0,0,32,15,RGB(255,0,255));
		push        0FF00FFh
		push        0Fh
		push        20h
		push        0
		push        0
		push        dword ptr[hTempDC]
		push        0Fh
		push        20h
		mov         ecx, dword ptr[this]
		mov         edx, dword ptr[ecx + 1Ch]
		add         edx, 30h
		push        edx
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		add         ecx, 8
		push        ecx
		push        dword ptr[hdc]
		call        TransparentBlt

		//if (m_player_status == BEGIN) 开始游戏时人物的动画
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 38h], 0
		jne         L1

		//SelectObject(hTempDC, m_hBmpPlayerStart)
		mov         eax, dword ptr[this]
		push        dword ptr[eax + 4]
		push		dword ptr[hTempDC]
		call		SelectObject

		//TransparentBlt(hdc, m_player_x, m_player_y, 48, 64, hTempDC, m_Start_nShowID * 48, 0, 48, 64, RGB(255, 0, 255))
		push        0FF00FFh
		push        40h
		push        30h
		push        0
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 14h], 30h
		push        ecx
		push        dword ptr[hTempDC]
		push        40h
		push        30h
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		push        ecx
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 18h]
		push        eax
		push        dword ptr[hdc]
		call        TransparentBlt
		jmp			end0

		//else if (m_player_status == MOVE) 人物移动时的动画
		L1 :
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 38h], 1
		jne         L2

		//if (m_direction == UP) 人物向上移动的动画
		mov         eax, dword ptr[this]
		cmp         dword ptr[eax + 3Ch], 0
		jne         M1

		//SelectObject(hTempDC, m_hBmpPlayerMove)
		mov         eax, dword ptr[this]
		push        dword ptr[eax + 8]
		mov         edx, dword ptr[hTempDC]
		push        edx
		call        SelectObject

		//TransparentBlt(hdc, m_player_x, m_player_y, 48, 64, hTempDC, m_Move_ShowId * 48, UP * 64, 48, 64, RGB(255, 0, 255))
		mov         esi, esp
		push        0FF00FFh
		push        40h
		push        30h
		push        0
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 30h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        40h
		push        30h
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
		//else if (m_direction == DOWN) 人物向下移动的动画
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

		//TransparentBlt(hdc, m_player_x, m_player_y, 48, 64, hTempDC, m_Move_ShowId * 48, DOWN * 64, 48, 64, RGB(255, 0, 255))
		mov         esi, esp
		push        0FF00FFh
		push        40h
		push        30h
		push        40h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 30h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        40h
		push        30h
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
		//else if (m_direction == LEFT) 人物向左移动的动画
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

		//TransparentBlt(hdc, m_player_x, m_player_y, 48, 64, hTempDC, m_Move_ShowId * 48, LEFT * 64, 48, 64, RGB(255, 0, 255))
		push        0FF00FFh
		push        40h
		push        30h
		push        80h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 30h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        40h
		push        30h
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
		//else if (m_direction == RIGHT) 人物向右移动的动画
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

		//TransparentBlt(hdc, m_player_x, m_player_y, 48, 64, hTempDC, m_Move_ShowId * 48, RIGHT * 64, 48, 64, RGB(255, 0, 255))
		push        0FF00FFh
		push        40h
		push        30h
		push        0C0h
		mov         eax, dword ptr[this]
		imul        ecx, dword ptr[eax + 20h], 30h
		push        ecx
		mov         edx, dword ptr[hTempDC]
		push        edx
		push        40h
		push        30h
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
		//else if (m_player_status == DIE) 人物死亡的动画
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

		//TransparentBlt(hdc, m_player_x, m_player_y - 36, 48, 100, hTempDC, (11 - m_DieShowID) * 48, 0, 48, 100, RGB(255, 0, 255))
		push        0FF00FFh
		push        64h
		push        30h
		push        0
		mov         eax, dword ptr[this]
		mov         ecx, 0Bh
		sub         ecx, dword ptr[eax + 28h]
		imul        edx, ecx, 30h
		push        edx
		mov         eax, dword ptr[hTempDC]
		push        eax
		push        64h
		push        30h
		mov         ecx, dword ptr[this]
		mov         edx, dword ptr[ecx + 1Ch]
		sub         edx, 24h
		push        edx
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		push        ecx
		mov         edx, dword ptr[hdc]
		push        edx
		call        TransparentBlt

		end0 :
		//DeleteObject(hTempDC) 删除DC对象
		mov         eax, dword ptr[hTempDC]
		push        eax
		call        DeleteObject
	}
}

//根据人物位图的位置与障碍物位置的关系判断人物是否可以移动
void CPlayerOne::PlayerMove(int FX, CGameMap& gameMap, CGameProps& gameprop, CPlaySound& playSound)
{
	int temp_x;
	int temp_y;
	int nPicture_x;
	int nPicture_y;
	int nBlock_x;
	int nBlock_y;


	_asm {
		// 根据人物位图下中坐标判断是否有障碍物
		// 将坐标转换成对应地图数组坐标
		//temp_x = (m_player_x - 20 + 24) / 40;
		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 18h]
		add         eax, 4
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_x], eax


		//temp_y = (m_player_y + 64 - 41) / 40;
		mov         eax, dword ptr[this]
		mov         eax, dword ptr[eax + 1Ch]
		add         eax, 17h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_y], eax

		//初始化为0
		mov         dword ptr[nPicture_x], 0
		mov         dword ptr[nPicture_y], 0
		mov         dword ptr[nBlock_x], 0
		mov         dword ptr[nBlock_y], 0


		// 移动
		//if (FX == 'A') 左移
		cmp         dword ptr[FX], 41h
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

		// 若人物位图最左侧位置大于障碍物最右侧位置，且人物位置大于地图侧边缘，则进行左移
		LA1 :
		mov         eax,dword ptr [gameprop]
		push        eax
		mov         ecx,dword ptr [this]
		mov         edx,dword ptr [ecx]
		mov         ecx,dword ptr [this]
		mov         eax,dword ptr [edx+14h]
		call        eax

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		sub         ecx, 5
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 18h], ecx

		//if (FX == 'D') 右移
		LA2 :
		cmp         dword ptr[FX], 44h
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

		// 若人物位图最右侧位置大于障碍物最左侧位置，且人物位置小于地图右侧边缘，则进行右移
		LD1 :
		mov         eax,dword ptr [gameprop]
		push        eax
		mov         ecx,dword ptr [this]
		mov         edx,dword ptr [ecx]
		mov         ecx,dword ptr [this]
		mov         eax,dword ptr [edx+14h]
		call        eax

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 18h]
		add         ecx, 5
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 18h], ecx

		//if (FX == 'W') 上移
		LD2 :
		cmp         dword ptr[FX], 57h
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

		// 若人物位图最上侧位置大于障碍物最下侧位置，且人物位置小于地图上侧边缘，则进行上移
		LW1 :
		mov         eax,dword ptr [gameprop]
		push        eax
		mov         ecx,dword ptr [this]
		mov         edx,dword ptr [ecx]
		mov         ecx,dword ptr [this]
		mov         eax,dword ptr [edx+14h]
		call        eax

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		sub         ecx, 5
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 1Ch], ecx

		//if (FX == 'S') 下移
		LW2 :
		cmp         dword ptr[FX], 53h
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

		// 若人物位图最下侧位置大于障碍物最上侧位置，且人物位置小于地图下侧边缘，则进行下移
		LS1 :
		mov         eax,dword ptr [gameprop]
		push        eax
		mov         ecx,dword ptr [this]
		mov         edx,dword ptr [ecx]
		mov         ecx,dword ptr [this]
		mov         eax,dword ptr [edx+14h]
		call        eax

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 1Ch]
		add         ecx, 5
		mov         edx, dword ptr[this]
		mov         dword ptr[edx + 1Ch], ecx
		LS2 :
	}
}

//放置泡泡
void CPlayerOne::CreateBubble(HINSTANCE hIns, CGameMap& gameMap, list<CBubble*>& lstBubble, CPlaySound& playSound, int x, int y)
{
	//-------坐标转换-------------------//
	int temp_x;
	int temp_y;
	CBubble* bubble = new CBubble;
	_asm {
		//x += 15;
		mov         eax, dword ptr[x]
		add         eax, 0Fh
		mov         dword ptr[x], eax

		//y = y + 64 - 15;
		mov         eax, dword ptr[y]
		add         eax, 31h
		mov         dword ptr[y], eax

		//if (x >= 20 && x <= 620 && y >= 41 && y <= 561)
		cmp         dword ptr[x], 14h
		jl          end0
		cmp         dword ptr[x], 26Ch
		jg          end0
		cmp         dword ptr[y], 29h
		jl          end0
		cmp         dword ptr[y], 231h
		jg          end0

		// 将坐标转换成对应地图数组坐标
		//int temp_x = (x - 20) / 40;
		mov         eax, dword ptr[x]
		sub         eax, 14h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_x], eax

		//int temp_y = (y - 41) / 40;
		mov         eax, dword ptr[y]
		sub         eax, 29h
		cdq
		mov         ecx, 28h
		idiv        ecx
		mov         dword ptr[temp_y], eax

		// 判断该位置是否有障碍物 没有障碍物 允许放泡泡
		//if (gameMap.map_type[temp_y][temp_x] == No)
		imul        eax, dword ptr[temp_y], 3Ch
		add         eax, dword ptr[gameMap]
		mov         ecx, dword ptr[temp_x]
		cmp         dword ptr[eax + ecx * 4], 0
		jne         end0

		// 将该位置赋值
		//gameMap.map_type[temp_y][temp_x] = Popo;
		imul        eax, dword ptr[temp_y], 3Ch
		add         eax, dword ptr[gameMap]
		mov         ecx, dword ptr[temp_x]
		mov         dword ptr[eax + ecx * 4], 9

		// 确定泡泡位置
		//temp_x = temp_x * 40 + 20;
		imul        eax, dword ptr[temp_x], 28h
		add         eax, 14h
		mov         dword ptr[temp_x], eax

		//temp_y = temp_y * 40 + 41 - 1;
		imul        eax, dword ptr[temp_y], 28h
		add         eax, 28h
		mov         dword ptr[temp_y], eax

		// 创建泡泡
		//bubble->BubbleInit(hIns,temp_x,temp_y,m_bubblePower);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 34h]
		push        ecx
		mov         edx, dword ptr[temp_y]
		push        edx
		mov         eax, dword ptr[temp_x]
		push        eax
		mov         ecx, dword ptr[hIns]
		push        ecx
		mov         ecx, dword ptr[bubble]
		call        CBubble::BubbleInit

		//bubble->m_bubble_owner = OWNER_PLAYERONE;
		mov         eax, dword ptr[bubble]
		mov         dword ptr[eax + 28h], 1
		end0:
	}
	//新泡泡放入list
	lstBubble.push_back(bubble);

	// 放置泡泡音效
	playSound.Play(PUT_BUEBLE_SOUND);
}

//判断是否吃到道具
bool CPlayerOne::WhetherProp(CGameProps& gameprop)
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
		GreaterEnergybubble :
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
