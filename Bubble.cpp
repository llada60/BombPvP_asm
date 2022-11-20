#include "Bubble.h"
#pragma comment(lib,"Msimg32.lib")
CBubble::CBubble()
{
	m_bitmap_bubble = NULL;
	m_bitmap_shadow_bubble = NULL;
	m_bitmap_boom = NULL;
	m_nShowID = 0;
	m_nBubble_x = 0;
	m_nBubble_y = 0;
	m_nBubbleBj = 0;
	m_nBoomShowID = 0;
	m_nBubble_power = 4;
	m_bubble_owner = OWNER_PLAYERNO;
	for(int i = 0;i < 4;i++)
	{
		m_arrfx[i] = 0;
	}
}

CBubble::~CBubble()
{
	DeleteObject(m_bitmap_bubble);
	DeleteObject(m_bitmap_shadow_bubble);
	DeleteObject(m_bitmap_boom);
	m_bitmap_shadow_bubble = NULL;
	m_bitmap_bubble = NULL;
	m_bitmap_boom = NULL;
}

void CBubble::BubbleInit(HINSTANCE hIns, int x, int y, int power)
{
	m_bitmap_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BUBBLE));
	m_bitmap_shadow_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SHADOW_BUBBLE));
	m_bitmap_boom = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_EXPLOSION));
	m_nShowID = 2;
	m_nBubbleBj = 16;
	m_nBoomShowID = 16;
	this->m_nBubble_x = x;
	this->m_nBubble_y = y;
	this->m_nBubble_power = power;
}

void CBubble::BubbleShow(HDC hdc)
{
	HDC hdcMem=CreateCompatibleDC(hdc);
	// ≈›≈›“ı”∞
	SelectObject(hdcMem,m_bitmap_shadow_bubble);
	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y+28,35,16,hdcMem,(2-m_nShowID)*35,0,35,16,RGB(255,0,255));
	// ≈›≈›
	SelectObject(hdcMem,m_bitmap_bubble);
	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,44,41,hdcMem,(2-m_nShowID)*44,0,44,41,RGB(255,0,255));
	DeleteObject(hdcMem);
}


void CBubble::BoomShow(HDC hdc)
{
	HDC hdcMem=CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_boom);
	for(int i = 0;i < m_arrfx[0];i++)
	{
		if(16-m_nBoomShowID-i < 0)
			continue;
		TransparentBlt(hdc,m_nBubble_x,m_nBubble_y - 40*(i+1),40,40,hdcMem,
			(16-m_nBoomShowID-i)*40,0,40,40,RGB(255,0,255));
	}
	for(int i = 0;i < m_arrfx[1];i++)
	{
		if(16-m_nBoomShowID-i < 0)
			continue;
		TransparentBlt(hdc,m_nBubble_x,m_nBubble_y + 40*(i+1),40,40,hdcMem,
			(16-m_nBoomShowID-i)*40,40,40,40,RGB(255,0,255));
	}
	for(int i = 0;i < m_arrfx[2];i++)
	{
		if(16-m_nBoomShowID-i < 0)
			continue;
		TransparentBlt(hdc,m_nBubble_x - 40*(i+1),m_nBubble_y,40,40,hdcMem,
			(16-m_nBoomShowID-i)*40,80,40,40,RGB(255,0,255));
	}
	for(int i = 0;i < m_arrfx[3];i++)
	{
		if(16-m_nBoomShowID-i < 0)
			continue;
		TransparentBlt(hdc,m_nBubble_x + 40*(i+1),m_nBubble_y,40,40,hdcMem,
			(16-m_nBoomShowID-i)*40,120,40,40,RGB(255,0,255));
	}
	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,40,40,hdcMem,
			(16-m_nBoomShowID)/3*40,160,40,40,RGB(255,0,255));
	DeleteObject(hdcMem);
}
