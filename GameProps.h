#ifndef CGAMEPROPS_H_
#define CGAMEPROPS_H_

#include "Sys.h"
#include "GameMap.h"

enum PropType { noprop = 10, energybubble, energywater, rollerskate, redhead, powerball };

class CGameProps
{
public:
	CGameProps();
	~CGameProps();
public:
	HBITMAP m_bitmap_energybubble;
	HBITMAP m_bitmap_energywater;
	HBITMAP m_bitmap_rollerskate;
	HBITMAP m_bitmap_redhead;
	HBITMAP m_bitmap_powerball;
	int m_nShowID;
	int m_bj[MAP_WIDTH][MAP_HEIGHT];
	int energybubblewpos[EBNUMBER];
	int energybubblehpos[EBNUMBER];
	int energywaterwpos[EWNUMBER];
	int energywaterhpos[EWNUMBER];
	int rollerskatewpos[RSNUMBER];
	int rollerskatehpos[RSNUMBER];
	int	edheadwpos[RHNUMBER];
	int	edheadhpos[RHNUMBER];
	int	powerballwpos[PBNUMBER];
	int	powerballhpos[PBNUMBER];
	
public:
	void PropInit(HINSTANCE hIns, CGameMap& map);
	void PropPositionShow(HDC hdc);
};

#endif // !CGAMEPROPS_H_
