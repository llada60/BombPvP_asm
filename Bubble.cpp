#include "Bubble.h"
#pragma comment(lib,"Msimg32.lib")
CBubble::CBubble()
{
	_asm {
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 2Ch], 0 //m_bitmap_bubble = NULL;
		mov         dword ptr[eax + 30h], 0 // m_bitmap_shadow_bubble = NULL;
		mov         dword ptr[eax + 34h], 0 // m_bitmap_boom = NULL;
		mov         dword ptr[eax], 0 // m_nShowID = 0;
		mov         dword ptr[eax + 8], 0 // m_nBubble_x = 0;
		mov         dword ptr[eax + 0Ch], 0 // m_nBubble_y = 0;
		mov         dword ptr[eax + 4], 0 // m_nBubbleBj = 0;
		mov         dword ptr[eax + 24h], 0 // m_nBoomShowID = 0;
		mov         dword ptr[eax + 10h], 4 // m_nBubble_power = 4;
		mov         dword ptr[eax + 28h], OWNER_PLAYERNO // m_bubble_owner = OWNER_PLAYERNO;
		// for(int i = 0;i < 4;i++)
		//		m_arrfx[i] = 0;
		mov			ecx, 4
Forloop:
		mov         dword ptr[eax + (ecx-1) * 4 + 14h], 0
		loop		Forloop
	}
}

CBubble::~CBubble()
{
	_asm {
		// DeleteObject(m_bitmap_bubble);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[m_bitmap_bubble]
		push        ecx
		call        DeleteObject
		// DeleteObject(m_bitmap_shadow_bubble);
		mov         ecx, dword ptr[m_bitmap_shadow_bubble]
		push        ecx
		call        DeleteObject
		// DeleteObject(m_bitmap_boom);
		mov         ecx, dword ptr[m_bitmap_boom]
		push        ecx
		call        DeleteObject
		mov         eax, dword ptr[this]
		mov         dword ptr[eax + 30h], 0 // m_bitmap_shadow_bubble = NULL;
		mov         dword ptr[eax + 2Ch], 0 // m_bitmap_bubble = NULL;
		mov         dword ptr[eax + 34h], 0 // m_bitmap_boom = NULL;
	}	
}

void CBubble::BubbleInit(HINSTANCE hIns, int x, int y, int power)
{
	_asm {
		// m_bitmap_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BUBBLE));
		push        IDB_BUBBLE // 76h
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 2Ch], eax
		// m_bitmap_shadow_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SHADOW_BUBBLE));
		push        IDB_SHADOW_BUBBLE
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 30h], eax
		// m_bitmap_boom = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_EXPLOSION));
		push        IDB_EXPLOSION
		mov         eax, dword ptr[hIns]
		push        eax
		call        LoadBitmap
		mov         ecx, dword ptr[this]
		mov         dword ptr[ecx + 34h], eax
		mov         eax, dword ptr[this] 
		mov         dword ptr[eax], 2 // m_nShowID = 2;
		mov         dword ptr[eax + 4], 10h // m_nBubbleBj = 16;
		mov         dword ptr[eax + 24h], 10h // m_nBoomShowID = 16;
		// this->m_nBubble_x = x;
		mov         ecx, dword ptr[x]
		mov         dword ptr[eax + 8], ecx 
		// this->m_nBubble_y = y;
		mov         ecx, dword ptr[y]
		mov         dword ptr[eax + 0Ch], ecx 
		// this->m_nBubble_power = power;
		mov         ecx, dword ptr[power]
		mov         dword ptr[eax + 10h], ecx
	}
}

void CBubble::BubbleShow(HDC hdc)
{
	HDC hdcMem=CreateCompatibleDC(hdc);
	_asm {
		// ÅÝÅÝÒõÓ°
		// SelectObject(hdcMem, m_bitmap_shadow_bubble);
		mov         ecx, dword ptr[m_bitmap_shadow_bubble]
		push        ecx
		mov         edx, dword ptr[hdcMem]
		push        edx
		call        SelectObject
		// TransparentBlt(hdc,m_nBubble_x,m_nBubble_y+28,35,16,hdcMem,(2-m_nShowID)*35,0,35,16,RGB(255,0,255));
		push        0FF00FFh
		push        10h
		push        23h
		push        0
		mov         eax, dword ptr[m_nShowID]
		mov         ecx, 2
		sub         ecx, eax
		imul        ecx, 23h
		push        ecx
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        10h
		push        23h
		mov         edx, dword ptr[m_nBubble_y]
		add         edx, 1Ch
		push        edx
		mov         ecx, dword ptr[m_nBubble_x]
		push        ecx
		mov         edx, dword ptr[hdc]
		push        edx
		call        TransparentBlt
		// SelectObject(hdcMem,m_bitmap_bubble);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 2Ch]
		push        ecx
		mov         edx, dword ptr[hdcMem]
		push        edx
		call        SelectObject
		// TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,44,41,hdcMem,(2-m_nShowID)*44,0,44,41,RGB(255,0,255));
		push        0FF00FFh
		push        29h
		push        2Ch
		push        0
		mov         eax, dword ptr[this]
		mov         ecx, 2
		sub         ecx, dword ptr[eax]
		imul        ecx, 2Ch
		push        ecx
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        29h
		push        2Ch
		mov         ecx, dword ptr[this]
		mov         edx, dword ptr[ecx + 0Ch]
		push        edx
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 8]
		push        ecx
		mov         edx, dword ptr[hdc]
		push        edx
		call        TransparentBlt
		// DeleteObject(hdcMem);
		mov         eax, dword ptr[hdcMem]
		push        eax
		call        DeleteObject
	}
	// SelectObject(hdcMem, m_bitmap_shadow_bubble);
	// TransparentBlt(hdc,m_nBubble_x,m_nBubble_y+28,35,16,hdcMem,(2-m_nShowID)*35,0,35,16,RGB(255,0,255));
	// ÅÝÅÝ
	//SelectObject(hdcMem,m_bitmap_bubble);
	// TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,44,41,hdcMem,(2-m_nShowID)*44,0,44,41,RGB(255,0,255));
	// DeleteObject(hdcMem);
}


void CBubble::BoomShow(HDC hdc)
{
	HDC hdcMem=CreateCompatibleDC(hdc);
	_asm {
		// SelectObject(hdcMem,m_bitmap_boom);
		mov         eax, dword ptr[this]
		mov         ecx, dword ptr[eax + 34h]
		push        ecx
		mov         edx, dword ptr[hdcMem]
		push        edx
		call        SelectObject
		// for(int i = 0;i < m_arrfx[0];i++)
		xor			ecx, ecx // i = 0
L1:
		mov         edx, dword ptr[this]
		cmp			ecx, dword ptr[edx+14h] // m_arrfx[0]
		jge			L1Done
		// if (16 - m_nBoomShowID - i < 0)
		//		continue;
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h] 
		sub         eax, ecx
		jl			L1control
		// TransparentBlt(hdc, m_nBubble_x, m_nBubble_y - 40 * (i + 1), 40, 40, hdcMem, (16 - m_nBoomShowID - i) * 40, 0, 40, 40, RGB(255, 0, 255));
		push        0FF00FFh
		push        40
		push        40
		push        0
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		imul        eax, 40
		push        eax
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        40
		push        40
		// m_nBubble_y - 40*(i+1)
		mov         edx, 1
		add         edx, ecx
		imul        edx, 40
		mov         eax, dword ptr[this]
		mov         edi, dword ptr[eax + 0Ch]
		sub         edi, edx
		push        edi
		// m_nBubble_x
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 8]
		push        eax
		mov         eax, dword ptr[hdc]
		push        eax
		call        TransparentBlt
L1control:
		add			ecx,1
		jmp			L1
L1Done:
		// for(int i = 0;i < m_arrfx[2];i++)
		xor			ecx, ecx
L2:
		mov         edx, dword ptr[this]
		cmp			ecx, dword ptr[edx + 14h + 4] // m_arrfx[1]
		jge			L2Done
		// if (16 - m_nBoomShowID - i < 0)
		//		continue;
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		jl			L2control
		// TransparentBlt(hdc, m_nBubble_x, m_nBubble_y - 40 * (i + 1), 40, 40, hdcMem, (16 - m_nBoomShowID - i) * 40, 0, 40, 40, RGB(255, 0, 255));
		push        0FF00FFh
		push        40
		push        40
		push        40
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		imul        eax, 40
		push        eax
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        40
		push        40
		// m_nBubble_y + 40*(i+1)
		mov         edx, 1
		add         edx, ecx
		imul        edx, 40
		mov         eax, dword ptr[this]
		mov         edi, dword ptr[eax + 0Ch]
		add         edi, edx
		push        edi
		// m_nBubble_x
		mov         edx, dword ptr[this]
		mov         eax, dword ptr[edx + 8]
		push        eax
		mov         eax, dword ptr[hdc]
		push        eax
		call        TransparentBlt
L2control :
		add			ecx, 1
		jmp			L2
L2Done :
		xor ecx, ecx
		// for (int i = 0; i < m_arrfx[2]; i++)
L3 :
		mov         edx, dword ptr[this]
		cmp			ecx, dword ptr[edx + 14h + 8] // m_arrfx[2]
		jge			L3Done
		// if (16 - m_nBoomShowID - i < 0)
		//		continue;
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		jl			L3control
		// TransparentBlt(hdc, m_nBubble_x, m_nBubble_y - 40 * (i + 1), 40, 40, hdcMem, (16 - m_nBoomShowID - i) * 40, 0, 40, 40, RGB(255, 0, 255));
		push        0FF00FFh
		push        40
		push        40
		push        80
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		imul        eax, 40
		push        eax
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        40
		push        40
		// m_nBubble_y
		mov         eax, dword ptr[this]
		mov         edx, dword ptr[eax + 0Ch]
		push		edx
		// m_nBubble_x - 40*(i+1)
		mov			eax, 1
		add			eax, ecx
		imul		eax, 40
		mov         edx, dword ptr[this]
		mov         edi, dword ptr[edx + 8]
		sub			edi,eax
		push        edi
		mov         eax, dword ptr[hdc]
		push        eax
		call        TransparentBlt
L3control :
		add			ecx, 1
		jmp			L3
L3Done :
		xor ecx, ecx
		// for (int i = 0; i < m_arrfx[3]; i++)
L4 :
		mov         edx, dword ptr[this]
		cmp			ecx, dword ptr[edx + 14h + 12] // m_arrfx[3]
		jge			L4Done
		// if (16 - m_nBoomShowID - i < 0)
		//		continue;
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		jl			L4control
		// TransparentBlt(hdc, m_nBubble_x, m_nBubble_y - 40 * (i + 1), 40, 40, hdcMem, (16 - m_nBoomShowID - i) * 40, 0, 40, 40, RGB(255, 0, 255));
		push        0FF00FFh
		push        40
		push        40
		push        120
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		sub         eax, ecx
		imul        eax, 40
		push        eax
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        40
		push        40
		// m_nBubble_y
		mov         eax, dword ptr[this]
		mov         edx, dword ptr[eax + 0Ch]
		push		edx
		// m_nBubble_x + 40*(i+1)
		mov			eax, 1
		add			eax, ecx
		imul		eax, 40
		mov         edx, dword ptr[this]
		mov         edi, dword ptr[edx + 8]
		add			edi, eax
		push        edi
		mov         eax, dword ptr[hdc]
		push        eax
		call        TransparentBlt
L4control :
		add			ecx, 1
		jmp			L4
L4Done :
		// 	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,40,40,hdcMem,
		// (16 - m_nBoomShowID) / 3 * 40, 160, 40, 40, RGB(255, 0, 255));
		push        0FF00FFh
		push        40
		push        40
		push        160
		mov         eax, 16
		mov         edx, dword ptr[this]
		sub         eax, dword ptr[edx + 24h]
		imul        eax, 40
		xor			edx, edx // edxÇåÁã
		mov			ecx, 3
		idiv		ecx
		push        eax
		mov         eax, dword ptr[hdcMem]
		push        eax
		push        40
		push        40
		// m_nBubble_y
		mov         eax, dword ptr[this]
		mov         edx, dword ptr[eax + 0Ch]
		push		edx
		// m_nBubble_x
		mov         edx, dword ptr[this]
		mov         edi, dword ptr[edx + 8]
		push        edi
		mov         eax, dword ptr[hdc]
		push        eax
		call        TransparentBlt
		// DeleteObject(hdcMem);
		mov         eax, dword ptr[hdcMem]
		push        eax
		call        DeleteObject
	}
}
