#include "GameProps.h"

CGameProps::CGameProps()
{
	m_bitmap_energybubble = NULL;
	m_bitmap_energywater = NULL;
	m_bitmap_rollerskate = NULL;
	m_bitmap_redhead = NULL;
	m_bitmap_powerball = NULL;
	m_nShowID = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_bj[i][j] = noprop;
		}
	}
	for (int i = 0; i < EBNUMBER; i++)
	{
		energybubblewpos[i] = 0;
		energybubblehpos[i] = 0;
	}
	for (int i = 0; i < EWNUMBER; i++)
	{
		energywaterwpos[i] = 0;
		energywaterhpos[i] = 0;
	}

	for (int i = 0; i < RSNUMBER; i++)
	{
		rollerskatewpos[i] = 0;
		rollerskatehpos[i] = 0;
	}
	for (int i = 0; i < RHNUMBER; i++)
	{
		edheadwpos[i] = 0;
		edheadhpos[i] = 0;
	}

	for (int i = 0; i < PBNUMBER; i++)
	{
		powerballwpos[i] = 0;
		powerballhpos[i] = 0;
	}
}

CGameProps::~CGameProps()
{
	DeleteObject(m_bitmap_energybubble);
	DeleteObject(m_bitmap_energywater);
	DeleteObject(m_bitmap_rollerskate);
	DeleteObject(m_bitmap_redhead);
	DeleteObject(m_bitmap_powerball);
	m_bitmap_energybubble = NULL;
	m_bitmap_energywater = NULL;
	m_bitmap_rollerskate = NULL;
	m_bitmap_redhead = NULL;
	m_bitmap_powerball = NULL;
}

void CGameProps::PropInit(HINSTANCE hIns,CGameMap& map)
{
	// 设置随机数种子
	srand((unsigned int)time(0));
	//加载图片
	m_bitmap_energybubble = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WATER_BUBBLE));
	m_bitmap_energywater = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_POWER_WATER));
	m_bitmap_rollerskate = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SPEED_SHOE));
	m_bitmap_redhead = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAX_SPEED));
	m_bitmap_powerball = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAX_POWER));
	m_nShowID = 2;
	// 随机初始化道具位置
	int i = 0;
	while (i < EBNUMBER)
	{
		energybubblewpos[i] = rand()%MAP_WIDTH;
		energybubblehpos[i] = rand()%MAP_HEIGHT;
		if((map.map_type[energybubblehpos[i]][energybubblewpos[i]] == R_B_ || map.map_type[energybubblehpos[i]][energybubblewpos[i]]==Y_B_) && m_bj[energybubblehpos[i]][energybubblewpos[i]] == noprop)
		{
			m_bj[energybubblehpos[i]][energybubblewpos[i]] = energybubble;
			i++;
		}
	}
	int j = 0;
	while (j < EWNUMBER)
	{
		energywaterwpos[j] = rand()%MAP_WIDTH;
		energywaterhpos[j] = rand()%MAP_HEIGHT;
		if((map.map_type[energywaterhpos[j]][energywaterwpos[j]] == R_B_||map.map_type[energywaterhpos[j]][energywaterwpos[j]] == Y_B_) && m_bj[energywaterhpos[j]][energywaterwpos[j]] == noprop)
		{
			m_bj[energywaterhpos[j]][energywaterwpos[j]]=energywater;
			j++;
		}

	}
	int k = 0;
	while (k < RSNUMBER)
	{
		rollerskatewpos[k] = rand()%MAP_WIDTH;
		rollerskatehpos[k] = rand()%MAP_HEIGHT;
		if((map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == R_B_||map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == Y_B_) && m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == noprop)
		{
			m_bj[rollerskatehpos[k]][rollerskatewpos[k]] = rollerskate;
			k++;
		}

	}
	int l = 0;
	while (l < RHNUMBER)
	{
		edheadwpos[l] = rand()%MAP_WIDTH;
		edheadhpos[l] = rand()%MAP_HEIGHT;
		if((map.map_type[edheadhpos[l]][edheadwpos[l]] == R_B_ || map.map_type[edheadhpos[l]][edheadwpos[l]] == Y_B_) && m_bj[edheadhpos[l]][edheadwpos[l]] == noprop)
		{
			m_bj[edheadhpos[l]][edheadwpos[l]] = redhead;
			l++;
		}
	}
	int m = 0;
	while (m < PBNUMBER)
	{
		powerballwpos[m] = rand()%MAP_WIDTH;
		powerballhpos[m] = rand()%MAP_HEIGHT;
		if((map.map_type[powerballhpos[m]][powerballwpos[m]] == R_B_ || map.map_type[powerballhpos[m]][powerballwpos[m]] == Y_B_) && m_bj[powerballhpos[m]][powerballwpos[m]] == noprop)
		{
			m_bj[powerballhpos[m]][powerballwpos[m]] = powerball;
			m++;
		}
	}
}


void CGameProps::PropPositionShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	int x = 0;
	int y = 0;
	for (int i = 0; i < EBNUMBER; i++)
	{
		x = energybubblewpos[i] * 40 + 20;
		y = energybubblehpos[i] * 40 + 41;
		if( m_bj[energybubblehpos[i]][energybubblewpos[i]] == energybubble)
		{
			SelectObject(hdcMem,m_bitmap_energybubble);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int j = 0; j < EWNUMBER; j++)
	{
		x = energywaterwpos[j] * 40 + 20;
		y = energywaterhpos[j] * 40 + 41;
		if(m_bj[energywaterhpos[j]][energywaterwpos[j]] == energywater)
		{
			SelectObject(hdcMem,m_bitmap_energywater);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int k = 0; k < RSNUMBER; k++)
	{

		x = rollerskatewpos[k] * 40 + 20;
		y = rollerskatehpos[k] * 40 + 41;
		if(m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == rollerskate)
		{
			SelectObject(hdcMem,m_bitmap_rollerskate);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int m = 0; m < RHNUMBER; m++)
	{

		x = edheadwpos[m] * 40 + 20;
		y = edheadhpos[m] * 40 + 41;
		if(m_bj[edheadhpos[m]][edheadwpos[m]] == redhead)
		{
			SelectObject(hdcMem,m_bitmap_redhead);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}
	for (int n = 0; n < PBNUMBER; n++)
	{

		x = powerballwpos[n] * 40 + 20;
		y = powerballhpos[n] * 40 + 41;
		if(m_bj[powerballhpos[n]][powerballwpos[n]] == powerball)
		{
			SelectObject(hdcMem,m_bitmap_powerball);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}

	DeleteDC(hdcMem);
}
