#include "Player.h"

CPlayer::CPlayer(void)
{
	m_hBmpPlayerStart = NULL;
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
	m_bubblePower = 1;
}

CPlayer::~CPlayer(void)
{
	DeleteObject(m_hBmpPlayerStart);
	DeleteObject(m_hBmpPlayerMove);
	DeleteObject(m_hBmpPlayerDie);
	DeleteObject(m_hBmpPlayerShadow);
	m_hBmpPlayerStart = NULL;
	m_hBmpPlayerMove = NULL;
	m_hBmpPlayerDie = NULL;
	m_hBmpPlayerShadow = NULL;
}
