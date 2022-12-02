#include "Player.h"

CPlayer::CPlayer(void)
{
	_asm
	{
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 4], 0
		mov         dword ptr[eax + 8], 0
		mov         dword ptr[eax + 0Ch], 0
		mov         dword ptr[eax + 10h], 0
		mov         dword ptr[eax + 14h], 0
		mov         dword ptr[eax + 18h], 0
		mov         dword ptr[eax + 1Ch], 0
		mov         dword ptr[eax + 38h], 0
		mov         dword ptr[eax + 3Ch], 1
		mov         dword ptr[eax + 20h], 0
		mov         byte ptr[eax + 24h], 0
		mov         dword ptr[eax + 28h], 0
		mov         dword ptr[eax + 2Ch], 28h
		mov         dword ptr[eax + 30h], 1
		mov         dword ptr [eax+34h],1
	}
	/*m_hBmpPlayerStart = NULL;
	m_hBmpPlayerMove = NULL;
	m_hBmpPlayerDie = NULL;
	m_hBmpPlayerShadow = NULL;
	m_Start_nShowID = 0;
	m_player_x = 0;
	m_player_y = 0;
	m_player_status = BEGIN;
	m_direction = DOWN;
	m_Move_ShowId = 0;
	m_bMoveFlag = false;
	m_DieShowID = 0;
	m_speed_timer = _DEF_PLAYER_SPEED_TIMER;
	m_bubbleNum = 1;
	m_bubblePower = 1;*/
}

CPlayer::~CPlayer(void)
{
	_asm
	{
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 4]
		push        ecx
		call        DeleteObject

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 8]
		push        ecx
		call        DeleteObject

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 0Ch]
		push        ecx
		call        DeleteObject

		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 10h]
		push        ecx
		call        DeleteObject

		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 4], 0
		mov         dword ptr[eax + 8], 0
		mov         dword ptr[eax + 0Ch], 0
		mov         dword ptr[eax + 10h], 0
	}
	/*
	DeleteObject(m_hBmpPlayerStart);
	DeleteObject(m_hBmpPlayerMove);
	DeleteObject(m_hBmpPlayerDie);
	DeleteObject(m_hBmpPlayerShadow);
	m_hBmpPlayerStart = NULL;
	m_hBmpPlayerMove = NULL;
	m_hBmpPlayerDie = NULL;
	m_hBmpPlayerShadow = NULL;*/
}
