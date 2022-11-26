#include "GameMap.h"


CGameMap::CGameMap()
{
	m_bitmap_redBrick = NULL;
	m_bitmap_redHouse = NULL;
	m_bitmap_yellowBrick = NULL;
	m_bitmap_yellowHouse = NULL;
	m_bitmap_Tree = NULL;
	m_bitmap_Box = NULL;
	m_bitmap_blueHouse = NULL;
	m_bitmap_windUp = NULL;
	m_bitmap_windDown = NULL;
	m_bitmap_ShadowBlock = NULL;
	m_nShowID = 1;

	//for (int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		map_type[i][j] = 0;
	//	}
	//}

	int ptr1 = (int)map_type;
	__asm {
		//esi为map_type的首地址
		mov esi, ptr1
		mov ecx, MAP_HEIGHT
		mov ebx, MAP_WIDTH
		add ecx, ebx
		loop1:
			mov dword ptr[esi], 0
			add esi, 4
			dec ecx
			cmp ecx, 0
			jg loop1
	}



}

CGameMap::~CGameMap()
{
	DeleteObject(m_bitmap_redBrick);
	DeleteObject(m_bitmap_redHouse);
	DeleteObject(m_bitmap_yellowBrick);
	DeleteObject(m_bitmap_yellowHouse);
	DeleteObject(m_bitmap_Tree);
	DeleteObject(m_bitmap_Box);
	DeleteObject(m_bitmap_blueHouse);
	DeleteObject(m_bitmap_windUp);
	DeleteObject(m_bitmap_windDown);
	DeleteObject(m_bitmap_ShadowBlock);
	m_bitmap_redBrick = NULL;
	m_bitmap_redHouse = NULL;
	m_bitmap_yellowBrick = NULL;
	m_bitmap_yellowHouse = NULL;
	m_bitmap_Tree = NULL;
	m_bitmap_Box = NULL;
	m_bitmap_blueHouse = NULL;
	m_bitmap_windUp=NULL;
	m_bitmap_windDown=NULL;
}

void CGameMap::MapInit(HINSTANCE hIns)
{
	m_bitmap_redBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDBRICK));
	m_bitmap_redHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_REDHOUSE));
	m_bitmap_yellowBrick = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWBRICK));
	m_bitmap_yellowHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_YELLOWHOUSE));
	m_bitmap_Tree = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TREE));
	m_bitmap_Box = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BOX));
	m_bitmap_blueHouse = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BLUEHOUSE));
	m_bitmap_windUp = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WINDMILL_UP));
	m_bitmap_windDown = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WINDMILL_DOWN));
	m_bitmap_ShadowBlock = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_BLOCK));
	m_nShowID = 1;

	// 加载地图数据
	FILE *fp = NULL;
	fopen_s(&fp,"mapData/map_village1.txt","r");
	// 打开文件成功
	if (fp != NULL)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp,"%d",&map_type[i][j]);
			}
		}

		fclose(fp);
	}
	// 打开文件失败
	else
	{
		if ( MessageBox( NULL, TEXT("地图初始化失败!"), TEXT("加载程序错误"), MB_OK | MB_ICONERROR ) == IDOK )
		{
			PostQuitMessage(0);
		}
	}
}
void CGameMap::MapUpShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = MAP_WIDTH-1; j >= 0; j--)
		{
			x = j * 40 + 20;
			y = i * 40 + 41;

			if (map_type[i][j] == B_H_)
			{
				SelectObject(hdcMem,m_bitmap_blueHouse);
				TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255));
			}
			if (map_type[i][j] == R_H_)
			{
				SelectObject(hdcMem,m_bitmap_redHouse);
				TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255));
			}
			if (map_type[i][j] == Y_H_)
			{
				SelectObject(hdcMem,m_bitmap_yellowHouse);
				TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255));
			}

			if (map_type[i][j] == Tree)
			{
				SelectObject(hdcMem,m_bitmap_Tree);
				TransparentBlt(hdc,x,y-27,40,27,hdcMem,0,0,40,27,RGB(255,0,255));
			}

			if (map_type[i][j] == WIND)
			{
				SelectObject(hdcMem,m_bitmap_windUp);
				TransparentBlt(hdc,260,161,120,118,hdcMem,(1-m_nShowID)*120,0,120,118,RGB(255,0,255));
			}
			
		}
	}
	
	DeleteDC(hdcMem);
}
void CGameMap::MapShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = MAP_WIDTH-1; j >= 0; j--)
		{
			x = j * 40 + 20;
			y = i * 40 + 41;

			if (map_type[i][j] == B_H_)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_blueHouse);
				TransparentBlt(hdc,x,y,40,40,hdcMem,0,17,40,40,RGB(255,0,255));
			}
			if (map_type[i][j] == R_H_)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_redHouse);
				TransparentBlt(hdc,x,y,40,40,hdcMem,0,17,40,40,RGB(255,0,255));
			}
			if (map_type[i][j] == Y_H_)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_yellowHouse);
				TransparentBlt(hdc,x,y,40,40,hdcMem,0,17,40,40,RGB(255,0,255));
			}
			if (map_type[i][j] == R_B_)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_redBrick);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == Y_B_)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_yellowBrick);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == Tree)
			{
				SelectObject(hdcMem,m_bitmap_Tree);
				TransparentBlt(hdc,x,y,40,40,hdcMem,0,27,40,40,RGB(255,0,255));
			}
			if (map_type[i][j] == Box)
			{
				SelectObject(hdcMem,m_bitmap_ShadowBlock);
				TransparentBlt(hdc,x-3,y-1,45,45,hdcMem,0,0,45,45,RGB(255,0,255));
				SelectObject(hdcMem,m_bitmap_Box);
				BitBlt(hdc,x,y,40,40,hdcMem,0,0,SRCCOPY);
			}
			if (map_type[i][j] == WIND)
			{
			/*	SelectObject(hdcMem,m_bitmap_windUp);
				TransparentBlt(hdc,260,161,120,118,hdcMem,(1-m_nShowID)*120,0,120,118,RGB(255,0,255));*/
				SelectObject(hdcMem,m_bitmap_windDown);
				TransparentBlt(hdc,260,279,120,42,hdcMem,0,0,120,42,RGB(255,0,255));
			}
			
		}
	}
	
	DeleteDC(hdcMem);
}

void CGameMap::MapBlast(int i, int j, int power ,int *arr)
{
	switch (power)
	{
	case 1:
		// 泡泡威力为1格
		BlastBlock_One(i,j,arr);
		break;
	case 2:
		// 泡泡威力为2格
		BlastBlock_One(i,j,arr);
		BlastBlock_Two(i,j,arr);
		break;
	case 3:
		// 泡泡威力为3格
		BlastBlock_One(i,j,arr);
		BlastBlock_Two(i,j,arr);
		BlastBlock_Three(i,j,arr);
		break;
	case 4:
		// 泡泡威力为4格
		BlastBlock_One(i,j,arr);
		BlastBlock_Two(i,j,arr);
		BlastBlock_Three(i,j,arr);
		BlastBlock_Four(i,j,arr);
		break;
	default:
		BlastBlock_One(i,j,arr);
		break;
	}

}

void CGameMap::BlastBlock_One(int i, int j, int *arr)
{
	// //泡泡 →
	//if ( i < MAP_HEIGHT - 1 && map_type[i+1][j] <= Box && map_type[i+1][j] != No)
	//{
	//	map_type[i+1][j] = No;
	//}	
	//// 泡泡 ←
	//if ( i > 0 && map_type[i-1][j] <= Box && map_type[i-1][j] != No)
	//{
	//	map_type[i-1][j] = No;
	//}	
	// //泡泡 ↓
	//if ( j < MAP_WIDTH - 1 && map_type[i][j+1] <= Box && map_type[i][j+1] != No)
	//{
	//	map_type[i][j+1] = No;
	//}	
	// //泡泡 ↑
	//if ( j > 0 && map_type[i][j-1] <= Box && map_type[i][j-1] != No)
	//{
	//	map_type[i][j-1] = No;
	//}
	int ptr1 = (int)map_type;
	_asm{
		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax

		// 输入初始i， j
		mov edx, i
		mov ecx, j
		// 计算偏移，也就是这一个泡泡的上下左右位置i+1
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2
		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4*15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		// 开始判断该位置是否能置为空
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// 置空
		mov dword ptr[eax], 0
		
	P2:
		mov edx, i
		mov ecx, j
		cmp edx, 0
		jng P3
		// 计算偏置i-1
		sub edx, 1
		push edx
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp dword ptr[eax], 3
		ja  P3
		cmp dword ptr[eax], 0
		je  P3
		mov dword ptr[eax], 0
		
	P3:
		mov edx, i
		mov ecx, j
		// 计算偏置j+1
		add ecx, 1
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp ecx, MAP_WIDTH
		jg P4
		cmp dword ptr[eax], 3
		ja  P4
		cmp dword ptr[eax], 0
		je  P4
		mov dword ptr[eax], 0

	P4:
		mov edx, i
		mov ecx, j
		cmp ecx, 0
		jng P5
		// 计算偏置j-1
		sub ecx, 1
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp dword ptr[eax], 3
		ja  P5
		cmp dword ptr[eax], 0
		je  P5
		mov dword ptr[eax], 0
		
	P5:
		//pop edx
		//pop ecx
		//pop ebx
		//pop edi
		//pop eax
	}

}

void CGameMap::BlastBlock_Two(int i, int j, int *arr)
{
	/*if ( i < MAP_HEIGHT - 2 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box && map_type[i+2][j] != No)
	{
		map_type[i+2][j] = No;
	}
	if ( i > 1 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-2][j] != No)
	{
		map_type[i-2][j] = No;
	}
	if ( j < MAP_WIDTH - 2 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+2] != No)
	{
		map_type[i][j+2] = No;
	}
	if ( j > 1 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-2] != No)
	{
		map_type[i][j-2] = No;
	}*/
	int ptr1 = (int)map_type;
	_asm {
		
		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// 输入初始i， j
		mov edx, i
		mov ecx, j
		// 存储i+1
		add edx, 1
		mov esi, edx
		// 计算偏移，也就是这一个泡泡的上下左右位置i+2
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+1,j的位置
		cmp dword ptr[eax], 3
		ja  P2
		


		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		// 开始判断该位置是否能置为空
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// 置空
		mov dword ptr[eax], 0

	P2:
		mov edx, i
		mov ecx, j
		// 存储i-1
		sub edx, 1
		mov esi, edx

		cmp edx, 1
		jng P3
		// 计算偏置i-2
		sub edx, 1

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i-1,j的位置
		cmp dword ptr[eax], 3
		ja  P3
		

		push edx
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp dword ptr[eax], 3
		ja  P3
		cmp dword ptr[eax], 0
		je  P3
		mov dword ptr[eax], 0

	P3:
		mov edx, i
		mov ecx, j
		// 存储j+1
		add ecx, 1
		mov esi, ecx

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, esi
		add eax, esi
		add eax, esi
		add eax, esi
		add eax, ebx

		// 判断i,j+1的位置
		cmp dword ptr[eax], 3
		ja  P4
		

		// 计算偏置j+2
		add ecx, 1
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp ecx, MAP_WIDTH
		jg P4
		cmp dword ptr[eax], 3
		ja  P4
		cmp dword ptr[eax], 0
		je  P4
		mov esi, 0
		mov dword ptr[eax], esi

	P4 :
		mov edx, i
		mov ecx, j
		cmp ecx, 1
		jng P5
		// 计算j-1
		sub ecx, 1
		mov esi, ecx

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, esi
		add eax, esi
		add eax, esi
		add eax, esi
		add eax, ebx

		// 判断i,j-1的位置
		cmp dword ptr[eax], 3
		ja  P5
		

		// 计算偏置j-2
		sub ecx, 1
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		cmp dword ptr[eax], 3
		ja  P5
		cmp dword ptr[eax], 0
		je  P5
		mov dword ptr[eax], 0

	P5:
		//pop esi
		//pop eax
		//pop edi
		//pop ebx
		//pop ecx
		//pop edx
		//pop esp
	}
}

void CGameMap::BlastBlock_Three(int i, int j, int *arr)
{
	//if ( i < MAP_HEIGHT - 3 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box &&  map_type[i+3][j] <= Box && map_type[i+3][j] != No)
	//{
	//	map_type[i+3][j] = No;
	//}
	//if ( i > 2 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-3][j] <= Box && map_type[i-3][j] != No)
	//{
	//	map_type[i-3][j] = No;
	//}
	//if ( j < MAP_WIDTH - 3 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+3] <= Box && map_type[i][j+3] != No)
	//{
	//	map_type[i][j+3] = No;
	//}
	//if ( j > 2 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-3] <= Box && map_type[i][j-3] != No)
	//{
	//	map_type[i][j-3] = No;
	//}
	int ptr1 = (int)map_type;
	_asm {

		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// 输入初始i， j
		mov edx, i
		mov ecx, j
		// 存储i+1
		add edx, 1
		mov esi, edx
		mov ebx, ptr1
		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+1,j的位置
		cmp dword ptr[eax], 3
		ja  P2

		// 存储i+2
		add edx, 1
		mov esi, edx

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+2,j的位置
		cmp dword ptr[eax], 3
		ja  P2




		// 计算偏移，也就是这一个泡泡的上下左右位置i+3
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+3,j的位置
		cmp dword ptr[eax], 3
		ja  P2



		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		// 开始判断该位置是否能置为空
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// 置空
		mov dword ptr[eax], 0

		P2:
			mov edx, i
			mov ecx, j
			cmp edx, 2
			jng P3
			// 存储i-1
			sub edx, 1
			mov esi, edx


			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, esi
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx

			// 判断i-1,j的位置
			cmp dword ptr[eax], 3
			ja  P3
			
			// 存储i-2
			sub edx, 1
			mov esi, edx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, esi
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx

			// 判断i-2,j的位置
			cmp dword ptr[eax], 3
			ja  P3

			// i-3, j
			sub edx, 1

			push edx
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp dword ptr[eax], 3
			ja  P3
			cmp dword ptr[eax], 0
			je  P3
			mov dword ptr[eax], 0

		P3:
			mov edx, i
			mov ecx, j
			// 存储j+1
			add ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j+1的位置
			cmp dword ptr[eax], 3
			ja  P4

			// 存储j+2
			add ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j+2的位置
			cmp dword ptr[eax], 3
			ja  P4


			// 计算偏置j+3
			add ecx, 1
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp ecx, MAP_WIDTH
			jg P4
			cmp dword ptr[eax], 3
			ja  P4
			cmp dword ptr[eax], 0
			je  P4
			mov esi, 0
			mov dword ptr[eax], esi

			P4 :
		mov edx, i
			mov ecx, j
			cmp ecx, 2
			jng P5
			// 计算j-1
			sub ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j-1的位置
			cmp dword ptr[eax], 3
			ja  P5

			// 计算j-2
			sub ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j-2的位置
			cmp dword ptr[eax], 3
			ja  P5


			// 计算偏置j-3
			sub ecx, 1
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp dword ptr[eax], 3
			ja  P5
			cmp dword ptr[eax], 0
			je  P5
			mov dword ptr[eax], 0

			P5:
		//pop esi
		//pop eax
		//pop edi
		//pop ebx
		//pop ecx
		//pop edx
		//pop esp
	}
}

void CGameMap::BlastBlock_Four(int i, int j, int *arr)
{
	//if ( i < MAP_HEIGHT - 4 && map_type[i+1][j] <= Box && map_type[i+2][j] <= Box &&  map_type[i+3][j] <= Box &&  map_type[i+4][j] <= Box && map_type[i+4][j] != No)
	//{
	//	map_type[i+4][j] = No;
	//}
	//if ( i > 3 && map_type[i-1][j] <= Box && map_type[i-2][j] <= Box && map_type[i-3][j] <= Box && map_type[i-4][j] <= Box && map_type[i-4][j] != No)
	//{
	//	map_type[i-4][j] = No;
	//}
	//if ( j < MAP_WIDTH - 4 && map_type[i][j+1] <= Box && map_type[i][j+2] <= Box && map_type[i][j+3] <= Box && map_type[i][j+4] <= Box && map_type[i][j+4] != No)
	//{
	//	map_type[i][j+4] = No;
	//}
	//if ( j > 3 && map_type[i][j-1] <= Box && map_type[i][j-2] <= Box && map_type[i][j-3] <= Box && map_type[i][j-4] <= Box && map_type[i][j-4] != No)
	//{
	//	map_type[i][j-4] = No;
	//}
	int ptr1 = (int)map_type;
	_asm {

		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// 输入初始i， j
		mov edx, i
		mov ecx, j
		// 存储i+1
		add edx, 1
		mov esi, edx
		mov ebx, ptr1
		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+1,j的位置
		cmp dword ptr[eax], 3
		ja  P2

		// 存储i+2
		add edx, 1
		mov esi, edx

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+2,j的位置
		cmp dword ptr[eax], 3
		ja  P2


		// 计算偏移，也就是这一个泡泡的上下左右位置i+3
		add edx, 1
		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, esi
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx

		// 判断i+3,j的位置
		cmp dword ptr[eax], 3
		ja  P2

		// 对i+4，j的判断
		add edx, 1
		cmp edx, MAP_HEIGHT
		jnb P2

		// 保护edx，因为后面要使用乘法
		push edx
		// 计算数组地址
		mov eax, 0
		mov eax, edx
		mov di, 4 * 15
		mul di
		pop edx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ecx
		add eax, ebx
		// 开始判断该位置是否能置为空
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// 置空
		mov dword ptr[eax], 0

		P2:
			mov edx, i
			mov ecx, j
			cmp edx, 3
			jng P3
			// 存储i-1
			sub edx, 1
			mov esi, edx


			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, esi
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx

			// 判断i-1,j的位置
			cmp dword ptr[eax], 3
			ja  P3

			// 存储i-2
			sub edx, 1
			mov esi, edx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, esi
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx

			// 判断i-2,j的位置
			cmp dword ptr[eax], 3
			ja  P3

			// i-3, j
			sub edx, 1
			mov esi, edx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, esi
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx

			// 判断i-3,j的位置
			cmp dword ptr[eax], 3
			ja  P3

			// i-4
			sub edx, 1

			push edx
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp dword ptr[eax], 3
			ja  P3
			cmp dword ptr[eax], 0
			je  P3
			mov dword ptr[eax], 0

			P3:
		mov edx, i
			mov ecx, j
			// 存储j+1
			add ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j+1的位置
			cmp dword ptr[eax], 3
			ja  P4

			// 存储j+2
			add ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j+2的位置
			cmp dword ptr[eax], 3
			ja  P4

			// 存储j+3
			add ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j+3的位置
			cmp dword ptr[eax], 3
			ja  P4

			// 计算偏置j+4
			add ecx, 1
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp ecx, MAP_WIDTH
			jg P4
			cmp dword ptr[eax], 3
			ja  P4
			cmp dword ptr[eax], 0
			je  P4
			mov esi, 0
			mov dword ptr[eax], esi

			P4 :
		mov edx, i
			mov ecx, j
			cmp ecx, 2
			jng P5
			// 计算j-1
			sub ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j-1的位置
			cmp dword ptr[eax], 3
			ja  P5

			// 计算j-2
			sub ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j-2的位置
			cmp dword ptr[eax], 3
			ja  P5
			// 计算j-3
			sub ecx, 1
			mov esi, ecx

			// 保护edx，因为后面要使用乘法
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, esi
			add eax, ebx

			// 判断i,j-3的位置
			cmp dword ptr[eax], 3
			ja  P5

			// 计算偏置j-4
			sub ecx, 1
			push edx
			// 计算数组地址
			mov eax, 0
			mov eax, edx
			mov di, 4 * 15
			mul di
			pop edx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ebx
			cmp dword ptr[eax], 3
			ja  P5
			cmp dword ptr[eax], 0
			je  P5
			mov dword ptr[eax], 0

			P5:
		//pop esi
		//pop eax
		//pop edi
		//pop ebx
		//pop ecx
		//pop edx
		//pop esp
	}
}