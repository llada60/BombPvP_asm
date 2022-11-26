#include "GameProps.h"
#include <Windows.h>
#define IS_USE_OUTPUT_DEBUG_PRINT   1

#if  IS_USE_OUTPUT_DEBUG_PRINT 

#define  OUTPUT_DEBUG_PRINTF(str)  OutputDebugPrintf(str)
void OutputDebugPrintf(const char* strOutputString, ...)
{
#define PUT_PUT_DEBUG_BUF_LEN   1024
	char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);  //_vsnprintf_s  _vsnprintf
	//vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);
	OutputDebugStringA(strBuffer);  //OutputDebugString    // OutputDebugStringW

}
#else 
#define  OUTPUT_DEBUG_PRINTF(str) 
#endif

CGameProps::CGameProps()
{
	m_bitmap_energybubble = NULL;
	m_bitmap_energywater = NULL;
	m_bitmap_rollerskate = NULL;
	m_bitmap_redhead = NULL;
	m_bitmap_powerball = NULL;
	m_nShowID = 0;

	// 初始化整张地图
	int m_bj_d = (int)m_bj;
	__asm
	{
		mov esi, m_bj_d
		xor edx,edx
		mov ebx, MAP_HEIGHT
		mov eax, MAP_WIDTH
		mul ebx
		loopmbj :
			mov dword ptr[esi], noprop
			add esi, 4
			dec eax
			cmp eax, 0
			jg loopmbj
	}
	/*for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_bj[i][j] = noprop;
		}
	}*/

	//初始化道具
	int ebwp = (int)energybubblewpos;
	int ebhp = (int)energybubblehpos;
	int ewwp = (int)energywaterwpos;
	int ewhp = (int)energywaterhpos;
	int rswp = (int)rollerskatewpos;
	int rshp = (int)rollerskatehpos;
	int ehwp = (int)edheadwpos;
	int ehhp = (int)edheadhpos;
	int pbwp = (int)powerballwpos;
	int pbhp = (int)powerballhpos;
	__asm
	{
		mov esi,ebwp
		mov edi,ebhp
		mov ebx, EBNUMBER
		loopeb:
			mov dword ptr[esi],0
			mov dword ptr[edi], 0
			add esi,4
			add edi,4
			dec ebx
			cmp ebx,0
			jg loopeb

		mov esi, ewwp
		mov edi, ewhp
		mov ebx, EWNUMBER
		loopew :
			mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg loopew

		mov esi, rswp
		mov edi, rshp
		mov ebx, RSNUMBER
		looprs :
			mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg looprs

		mov esi, ehwp
		mov edi, ehhp
		mov ebx, RHNUMBER
		loopeh :
			mov dword ptr[esi], 0
			mov dword ptr[edi], 0
			add esi, 4
			add edi, 4
			dec ebx
			cmp ebx, 0
			jg loopeh

		mov esi, pbwp
		mov edi, pbhp
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
	/*for (int i = 0; i < EBNUMBER; i++)
	{
		energybubblewpos[i] = 0;
		energybubblehpos[i] = 0;
	}*/
	/*for (int i = 0; i < EWNUMBER; i++)
	{
		energywaterwpos[i] = 0;
		energywaterhpos[i] = 0;
	}*/

	/*for (int i = 0; i < RSNUMBER; i++)
	{
		rollerskatewpos[i] = 0;
		rollerskatehpos[i] = 0;
	}*/
	/*for (int i = 0; i < RHNUMBER; i++)
	{
		edheadwpos[i] = 0;
		edheadhpos[i] = 0;
	}*/

	/*for (int i = 0; i < PBNUMBER; i++)
	{
		powerballwpos[i] = 0;
		powerballhpos[i] = 0;
	}*/
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
	/*int ebwp = (int)energybubblewpos;
	int ebhp = (int)energybubblehpos;*/
	//int i = 0;
	//__asm
	//{
	//	mov dword ptr[i],0
	//	next_i_init:
	//		cmp dword ptr[i], EBNUMBER
	//		jge next_j_init
	//		//energybubblewpos[i] = rand()%MAP_WIDTH;
	//		mov esi, esp
	//		call dword ptr[rand]
	//		cmp  esi, esp
	//		call __RTC_CheckEsp(0A15AAh)
	//		cdq
	//		mov  ecx, MAP_WIDTH
	//		idiv eax,ecx
	//		mov  eax, dword ptr[i]
	//		mov  ecx, dword ptr[this]
	//		mov  dword ptr[ecx + eax * 4 + 324h], edx
	//		//energybubblehpos[i] = rand()%MAP_HEIGHT;
	//		mov esi, esp
	//		call dword ptr[\_\_imp\_\_rand(0C11C8h)]
	//		cmp  esi, esp
	//		call \_\_RTC\_CheckEsp(0A15AAh)
	//		cdq
	//		mov  ecx, MAP_HEIGHT
	//		idiv eax, ecx
	//		mov  eax, dword ptr[i]
	//		mov  ecx, dword ptr[this]
	//		mov  dword ptr[ecx + eax * 4 + 324h], edx
	//		//if((map.map_type[energybubblehpos[i]][energybubblewpos[i]] == R_B_ || map.map_type[energybubblehpos[i]][energybubblewpos[i]]==Y_B_) && m_bj[energybubblehpos[i]][energybubblewpos[i]] == noprop)
	//		mov eax,dword ptr[i]
	//		mov ecx,dword ptr[this]
	//		imul edx,dword ptr[ecx+eax*4+34Ch],3Ch
	//		add edx,dword ptr[map]
	//		mov eax,dword ptr[i]
	//		mov ecx, dword ptr[this]
	//		mov eax, dword ptr[ecx + eax * 4 + 324h]
	//		cmp dword ptr[edx + eax * 4], 1
	//		je cmpand
	//		mov eax,dword ptr[i]
	//		mov ecx,dword ptr[this]
	//		imul edx,dword ptr[ecx+eax*4+34Ch],3Ch
	//		add edx,dword ptr[map]
	//		mov eax,dword ptr[i]
	//		mov ecx,dword ptr[this]
	//		mov eax,dword ptr[ecx+eax*4+324h]
	//		cmp dword ptr[ecx+eax*4],2
	//		jne next_j_init
	//		cmpand:
	//			mov eax,dword ptr[i]
	//			mov ecx,dword ptr[this]
	//			imul edx,dword ptr[ecx+eax*4+34Ch],34h
	//			mov eax,dword ptr[this]
	//			lea ecx,[eax+edx+18h]
	//			mov edx,dword ptr[i]
	//			mov eax,dword ptr[this]
	//			mov edx,dword ptr[eax+edx*4+324h]
	//			cmp dword ptr[ecx+edx*4],0Ah
	//			jne next_j_init
	//			//m_bj[energybubblehpos[i]][energybubblewpos[i]] = energybubble;
	//			mov eax,dword ptr[i]
	//			mov ecx,dword ptr[this]
	//			imul edx,dword ptr[ecx+eax*4+34Ch],34h
	//			mov eax,dword ptr[this]
	//			lea ecx,[eax+edx+18h]
	//			mov edx,dword ptr[i]
	//			mov eax,dword ptr[this]
	//			mov edx,dword ptr[eax+edx*4+324h]
	//			mov dword ptr[ecx+edx*4],0Bh
	//			//i++
	//			mov eax,dword ptr[i]
	//			add eax,1
	//			mov dword ptr[i],eax
	//			jmp next_i_init
	//	next_j_init:
	//}
	int j = 0;
	int m_bj_a = (int)m_bj;
	while (j < EWNUMBER)
	{
		energywaterwpos[j] = rand()%MAP_WIDTH;
		energywaterhpos[j] = rand()%MAP_HEIGHT;
		int ewwp = energywaterwpos[j];
		int ewhp = energywaterhpos[j];
		if((map.map_type[energywaterhpos[j]][energywaterwpos[j]] == R_B_||map.map_type[energywaterhpos[j]][energywaterwpos[j]] == Y_B_) && m_bj[energywaterhpos[j]][energywaterwpos[j]] == noprop)
		{
			__asm
			{
				//m_bj[energywaterhpos[j]][energywaterwpos[j]]=energywater;
				//j++;
				mov esi,m_bj_a
				xor edx,edx
				mov eax, ewhp
				mov ecx, MAP_WIDTH
				mul ecx
				add eax,ewwp
				mov dword ptr[esi+4*eax], energywater
				add dword ptr[j],1
			}
			
		}

	}
	int k = 0;
	while (k < RSNUMBER)
	{
		rollerskatewpos[k] = rand()%MAP_WIDTH;
		rollerskatehpos[k] = rand()%MAP_HEIGHT;
		int rswp = rollerskatewpos[k];
		int rshp = rollerskatehpos[k];
		if((map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == R_B_||map.map_type[rollerskatehpos[k]][rollerskatewpos[k]] == Y_B_) && m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == noprop)
		{
			__asm
			{
				//m_bj[rollerskatehpos[k]][rollerskatewpos[k]] = rollerskate;
				//k++;
				mov esi, m_bj_a
				xor edx, edx
				mov eax, rshp
				mov ecx, MAP_WIDTH
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
		edheadwpos[l] = rand()%MAP_WIDTH;
		edheadhpos[l] = rand()%MAP_HEIGHT;
		int ehwp = edheadwpos[l];
		int ehhp = edheadhpos[l];
		if((map.map_type[edheadhpos[l]][edheadwpos[l]] == R_B_ || map.map_type[edheadhpos[l]][edheadwpos[l]] == Y_B_) && m_bj[edheadhpos[l]][edheadwpos[l]] == noprop)
		{
			//m_bj[edheadhpos[l]][edheadwpos[l]] = redhead;
			//l++;
			__asm
			{
				mov esi, m_bj_a
				xor edx, edx
				mov eax, ehhp
				mov ecx, MAP_WIDTH
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
		powerballwpos[m] = rand()%MAP_WIDTH;
		powerballhpos[m] = rand()%MAP_HEIGHT;
		int pbwp = powerballwpos[m];
		int pbhp = powerballhpos[m];
		if((map.map_type[powerballhpos[m]][powerballwpos[m]] == R_B_ || map.map_type[powerballhpos[m]][powerballwpos[m]] == Y_B_) && m_bj[powerballhpos[m]][powerballwpos[m]] == noprop)
		{
			//m_bj[powerballhpos[m]][powerballwpos[m]] = powerball;
			//m++;
			__asm
			{
				mov esi, m_bj_a
				xor edx, edx
				mov eax, pbhp
				mov ecx, MAP_WIDTH
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
			xor edx,edx
			mov ebx,i
			mov esi,ebwp
			mov eax,dword ptr[esi+4*ebx]
			mov ecx,40
			imul ecx
			add eax,20
			mov x,eax
			//y = energybubblehpos[i] * 40 + 41;
			xor edx, edx
			mov esi, ebhp
			mov eax, dword ptr[esi + 4 * ebx]
			mov ecx, 40
			imul ecx
			add eax, 41
			mov y, eax
		}
		if( m_bj[energybubblehpos[i]][energybubblewpos[i]] == energybubble)
		{
			SelectObject(hdcMem,m_bitmap_energybubble);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
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
		if(m_bj[energywaterhpos[j]][energywaterwpos[j]] == energywater)
		{
			SelectObject(hdcMem,m_bitmap_energywater);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
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
		if(m_bj[rollerskatehpos[k]][rollerskatewpos[k]] == rollerskate)
		{
			SelectObject(hdcMem,m_bitmap_rollerskate);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
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
		
		
		if(m_bj[edheadhpos[m]][edheadwpos[m]] == redhead)
		{
			SelectObject(hdcMem,m_bitmap_redhead);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
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
		
		if(m_bj[powerballhpos[n]][powerballwpos[n]] == powerball)
		{
			SelectObject(hdcMem,m_bitmap_powerball);
			TransparentBlt(hdc,x,y,42,45,hdcMem,(2-m_nShowID)*42,0,42,45,RGB(255,0,255));
		}
	}

	DeleteDC(hdcMem);
}
