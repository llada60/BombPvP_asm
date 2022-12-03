#include "GameProps.h"

CGameProps::CGameProps()
{
	__asm
	{
		mov esi, dword ptr[this]
		mov dword ptr[esi],0		; m_bitmap_energybubble = NULL;
		mov dword ptr[esi + 4], 0	; m_bitmap_energywater = NULL;
		mov dword ptr[esi + 8], 0	; m_bitmap_rollerskate = NULL;
		mov dword ptr[esi + 0ch], 0	; m_bitmap_redhead = NULL;
		mov dword ptr[esi + 10h], 0	; m_bitmap_powerball = NULL;
		mov dword ptr[esi + 14h], 0	; m_nShowID = 0;
		
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_bj[i][j] = noprop;
		}
	}
	//初始化道具
	__asm
	{
		mov eax,dword ptr[this]
		add eax,324h
		mov esi, eax
		add eax,0ch
		mov edi, eax
		mov ebx, EBNUMBER
		loopeb :
		mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg loopeb

			add eax,0ch
			mov esi, eax
			add eax,0ch
			mov edi, eax
			mov ebx, EWNUMBER
			loopew :
		mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg loopew

			add eax, 0ch
			mov esi, eax
			add eax, 0ch
			mov edi, eax
			mov ebx, RSNUMBER
			looprs :
		mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg looprs

			add eax, 0ch
			mov esi, eax
			add eax, 0ch
			mov edi, eax
			mov ebx, RHNUMBER
			loopeh :
		mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg loopeh

			add eax, 0ch
			mov esi, eax
			add eax, 0ch
			mov edi, eax
			mov ebx, PBNUMBER
			looppb :
		mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg looppb
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

void CGameProps::PropInit(HINSTANCE hIns, CGameMap& map)
{
	// 设置随机数种子
	srand((unsigned int)time(0));
	//加载图片
	m_bitmap_energybubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_WATER_BUBBLE));
	m_bitmap_energywater = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_POWER_WATER));
	m_bitmap_rollerskate = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SPEED_SHOE));
	m_bitmap_redhead = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_MAX_SPEED));
	m_bitmap_powerball = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_MAX_POWER));
	m_nShowID = 2;
	// 随机初始化道具位置
	int i = 0;
	
	int m_bj_a = (int)m_bj;
	//while (i < EBNUMBER)
	//{
	//	energybubblewpos[i] = rand() % MAP_WIDTH;
	//	energybubblehpos[i] = rand() % MAP_HEIGHT;
	//	int ebwp = energybubblewpos[i];
	//	int ebhp = energybubblehpos[i];
	//	if ((map.map_type[energybubblehpos[i]][energybubblewpos[i]] == R_B_ || map.map_type[energybubblehpos[i]][energybubblewpos[i]] == Y_B_) && m_bj[energybubblehpos[i]][energybubblewpos[i]] == noprop)
	//	{
	//		__asm
	//		{
	//			/*m_bj[energybubblehpos[i]][energybubblewpos[i]] = energybubble;
	//			i++;*/
	//			mov esi, m_bj_a
	//			xor edx, edx
	//			mov eax, ebhp
	//			mov ecx, MAP_HEIGHT
	//			mul ecx
	//			add eax, ebwp
	//			mov dword ptr[esi + 4 * eax], energybubble
	//			add dword ptr[i], 1
	//		}
	//	}
	//}
	__asm
	{
		; ebnumber bomb 循环
		circle_eb :
		cmp dword ptr[i], EBNUMBER
			jge finish
			; energybubblewpos[i] = rand() % MAP_WIDTH;
		push eax
			xor edx, edx
			call rand
			CDQ
			mov ebx, MAP_WIDTH
			idiv ebx
			pop eax
			mov eax, dword ptr[i]
			mov ecx, dword ptr[this]
			mov dword ptr[ecx + eax * 4 + 324h], edx
			push edx; ebwp
			; energybubblehpos[i] = rand() % MAP_HEIGHT;
		push eax
			xor eax, eax
			call rand
			CDQ
			mov ebx, MAP_HEIGHT
			idiv ebx
			pop eax
			mov eax, dword ptr[i]
			mov ecx, dword ptr[this]
			mov dword ptr[ecx + eax * 4 + 338h], edx
			push edx; ebhp
			; if比较
			pop ecx; ebhp
			imul edx, ecx, 3Ch
			add edx, dword ptr[map]
			pop eax; ebwp
			cmp dword ptr[edx + eax * 4], R_B_
			je andcompare
			cmp dword ptr[edx + eax * 4], Y_B_
			jne out1
			andcompare :
		imul edx, ecx, 34h
			add edx, dword ptr[this]
			add edx, 18h
			cmp dword ptr[edx + eax * 4], noprop
			jne out1
			mov dword ptr[edx + eax * 4], energybubble
			add dword ptr[i], 1
			out1:
		jmp circle_eb
			finish :
		xor eax, eax
	}
	int j = 0;
	/*__asm
	{
		; ewnumber bomb 循环
		circle_ew :
		cmp dword ptr[j], EWNUMBER
			jge finish2
			; energywaterwpos[j] = rand() % MAP_WIDTH;
		push eax
			xor edx, edx
			call rand
			CDQ
			mov ebx, MAP_WIDTH
			idiv ebx
			pop eax
			mov eax, dword ptr[j]
			mov ecx, dword ptr[this]
			mov dword ptr[ecx + eax * 4 + 34ch], edx
			push edx; ebwp
			; energywaterhpos[j] = rand() % MAP_HEIGHT;
		push eax
			xor eax, eax
			call rand
			CDQ
			mov ebx, MAP_HEIGHT
			idiv ebx
			pop eax
			mov eax, dword ptr[j]
			mov ecx, dword ptr[this]
			mov dword ptr[ecx + eax * 4 + 360h], edx
			push edx; ebhp
			; if比较
			pop ecx; ebhp
			imul edx, ecx, 3Ch
			add edx, dword ptr[map]
			pop eax; ebwp
			cmp dword ptr[edx + eax * 4], R_B_
			je andcompare2
			cmp dword ptr[edx + eax * 4], Y_B_
			jne out2
			andcompare2 :
		imul edx, ecx, 34h
			add edx, dword ptr[this]
			add edx, 18h
			cmp dword ptr[edx + eax * 4], noprop
			jne out1
			mov dword ptr[edx + eax * 4], energywater
			add dword ptr[j], 1
			out2:
		jmp circle_ew
			finish2 :
		xor eax, eax
	}*/
	while (j < EWNUMBER)
	{
		energywaterwpos[j] = rand() % MAP_WIDTH;
		energywaterhpos[j] = rand() % MAP_HEIGHT;
		int ewwp = energywaterwpos[j];
		int ewhp = energywaterhpos[j];
		if ((map.map_type[energywaterhpos[j]][energywaterwpos[j]] == R_B_ || map.map_type[energywaterhpos[j]][energywaterwpos[j]] == Y_B_) && m_bj[energywaterhpos[j]][energywaterwpos[j]] == noprop)
		{
			__asm
			{
				//m_bj[energywaterhpos[j]][energywaterwpos[j]]=energywater;
				//j++;
				mov esi, m_bj_a
				xor edx, edx
				mov eax, ewhp
				mov ecx, MAP_HEIGHT
				mul ecx
				add eax, ewwp
				mov dword ptr[esi + 4 * eax], energywater
				add dword ptr[j], 1
			}
		}

	}
	int k = 0;
	while (k < RSNUMBER)
	{
		rollerskatewpos[k] = rand() % MAP_WIDTH;
		rollerskatehpos[k] = rand() % MAP_HEIGHT;
		int rswp = rollerskatewpos[k];
		int rshp = rollerskatehpos[k];
		if ((map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == R_B_ || map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == Y_B_) && m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == noprop)
		{
			__asm
			{
				//m_bj[rollerskatehpos[k]][rollerskatewpos[k]] = rollerskate;
				//k++;
				mov esi, m_bj_a
				xor edx, edx
				mov eax, rshp
				mov ecx, MAP_HEIGHT
				mul ecx
				add eax, rswp
				mov dword ptr[esi + 4 * eax], rollerskate
				add dword ptr[k], 1
			}
		}

	}
	int l = 0;
	while (l < RHNUMBER)
	{
		edheadwpos[l] = rand() % MAP_WIDTH;
		edheadhpos[l] = rand() % MAP_HEIGHT;
		int ehwp = edheadwpos[l];
		int ehhp = edheadhpos[l];
		if ((map.map_type[edheadhpos[l]][edheadwpos[l]] == R_B_ || map.map_type[edheadhpos[l]][edheadwpos[l]] == Y_B_) && m_bj[edheadhpos[l]][edheadwpos[l]] == noprop)
		{
			/*m_bj[edheadhpos[l]][edheadwpos[l]] = redhead;
			l++;*/
			__asm
			{
				mov esi, m_bj_a
				xor edx, edx
				mov eax, ehhp
				mov ecx, MAP_HEIGHT
				mul ecx
				add eax, ehwp
				mov dword ptr[esi + 4 * eax], redhead
				add dword ptr[l], 1
			}
		}
	}
	int m = 0;
	while (m < PBNUMBER)
	{
		powerballwpos[m] = rand() % MAP_WIDTH;
		powerballhpos[m] = rand() % MAP_HEIGHT;
		int pbwp = powerballwpos[m];
		int pbhp = powerballhpos[m];
		if ((map.map_type[powerballhpos[m]][powerballwpos[m]] == R_B_ || map.map_type[powerballhpos[m]][powerballwpos[m]] == Y_B_) && m_bj[powerballhpos[m]][powerballwpos[m]] == noprop)
		{
			/*m_bj[powerballhpos[m]][powerballwpos[m]] = powerball;
			m++;*/
			__asm
			{
				mov esi, m_bj_a
				xor edx, edx
				mov eax, pbhp
				mov ecx, MAP_HEIGHT
				mul ecx
				add eax, pbwp
				mov dword ptr[esi + 4 * eax], powerball
				add dword ptr[m], 1
			}
		}
	}
}


void CGameProps::PropPositionShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	int x = 0;
	int y = 0;
	int ebwp = (int)energybubblewpos;
	int ebhp = (int)energybubblehpos;
	for (int i = 0; i < EBNUMBER; i++)
	{
		__asm
		{
			//x = energybubblewpos[i] * 40 + 20;
			xor edx, edx
			mov ebx, i
			mov esi, ebwp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 20
			mov x, eax
			//y = energybubblehpos[i] * 40 + 41;
			xor edx, edx
			mov esi, ebhp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if (m_bj[energybubblehpos[i]][energybubblewpos[i]] == energybubble)
		{
			SelectObject(hdcMem, m_bitmap_energybubble);
			TransparentBlt(hdc, x, y, 42, 45, hdcMem, (2 - m_nShowID) * 42, 0, 42, 45, RGB(255, 0, 255));
		}
	}
	int ewwp = (int)energywaterwpos;
	int ewhp = (int)energywaterhpos;
	for (int j = 0; j < EWNUMBER; j++)
	{
		__asm
		{
			//x = energywaterwpos[j] * 40 + 20;
			xor edx, edx
			mov ebx, j
			mov esi, ewwp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 20
			mov x, eax
			//y = energywaterhpos[j] * 40 + 41;
			xor edx, edx
			mov esi, ewhp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if (m_bj[energywaterhpos[j]][energywaterwpos[j]] == energywater)
		{
			SelectObject(hdcMem, m_bitmap_energywater);
			TransparentBlt(hdc, x, y, 42, 45, hdcMem, (2 - m_nShowID) * 42, 0, 42, 45, RGB(255, 0, 255));
		}
	}
	int rswp = (int)rollerskatewpos;
	int rshp = (int)rollerskatehpos;
	for (int k = 0; k < RSNUMBER; k++)
	{
		__asm
		{
			//x = rollerskatewpos[k] * 40 + 20;
			xor edx, edx
			mov ebx, k
			mov esi, rswp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 20
			mov x, eax
			//y = rollerskatehpos[k] * 40 + 41;
			xor edx, edx
			mov esi, rshp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if (m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == rollerskate)
		{
			SelectObject(hdcMem, m_bitmap_rollerskate);
			TransparentBlt(hdc, x, y, 42, 45, hdcMem, (2 - m_nShowID) * 42, 0, 42, 45, RGB(255, 0, 255));
		}
	}
	int ehwp = (int)edheadwpos;
	int ehhp = (int)edheadhpos;
	for (int m = 0; m < RHNUMBER; m++)
	{
		__asm
		{
			//x = edheadwpos[m] * 40 + 20;
			xor edx, edx
			mov ebx, m
			mov esi, ehwp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 20
			mov x, eax
			//y = edheadhpos[m] * 40 + 41;
			xor edx, edx
			mov esi, ehhp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if (m_bj[edheadhpos[m]][edheadwpos[m]] == redhead)
		{
			SelectObject(hdcMem, m_bitmap_redhead);
			TransparentBlt(hdc, x, y, 42, 45, hdcMem, (2 - m_nShowID) * 42, 0, 42, 45, RGB(255, 0, 255));
		}
	}
	int pbwp = (int)powerballwpos;
	int pbhp = (int)powerballhpos;
	for (int n = 0; n < PBNUMBER; n++)
	{
		__asm
		{
			//x = powerballwpos[n] * 40 + 20;
			xor edx, edx
			mov ebx, n
			mov esi, pbwp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 20
			mov x, eax
			//y = powerballhpos[n] * 40 + 41;
			xor edx, edx
			mov esi, pbhp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if (m_bj[powerballhpos[n]][powerballwpos[n]] == powerball)
		{
			SelectObject(hdcMem, m_bitmap_powerball);
			TransparentBlt(hdc, x, y, 42, 45, hdcMem, (2 - m_nShowID) * 42, 0, 42, 45, RGB(255, 0, 255));
		}
	}

	DeleteDC(hdcMem);
}