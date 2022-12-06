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
	int ptr1 = (int)map_type;
	__asm {
		//esiΪmap_type���׵�ַ
		mov esi, ptr1
		mov ecx, MAP_HEIGHT
		mov ebx, MAP_WIDTH
		add ecx, ebx
		loop1 :
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
	m_bitmap_windUp = NULL;
	m_bitmap_windDown = NULL;
}

void CGameMap::MapInit(HINSTANCE hIns)
{
	m_bitmap_redBrick = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_REDBRICK));
	m_bitmap_redHouse = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_REDHOUSE));
	m_bitmap_yellowBrick = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_YELLOWBRICK));
	m_bitmap_yellowHouse = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_YELLOWHOUSE));
	m_bitmap_Tree = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_TREE));
	m_bitmap_Box = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BOX));
	m_bitmap_blueHouse = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BLUEHOUSE));
	m_bitmap_windUp = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_WINDMILL_UP));
	m_bitmap_windDown = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_WINDMILL_DOWN));
	m_bitmap_ShadowBlock = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SHADOW_BLOCK));
	m_nShowID = 1;

	// ���ص�ͼ����
	FILE* fp = NULL;
	fopen_s(&fp, "mapData/map_village1.txt", "r");
	// ���ļ��ɹ�
	if (fp != NULL)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d", &map_type[i][j]);
			}
		}

		fclose(fp);
	}
	// ���ļ�ʧ��
	else
	{
		if (MessageBox(NULL, TEXT("��ͼ��ʼ��ʧ��!"), TEXT("���س������"), MB_OK | MB_ICONERROR) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
}
void CGameMap::MapUpShow(HDC hdc)
{
	HDC hdcMem;
	int x1;
	int x, y;
	__asm {
		mov dword ptr[x1], esp
		mov  eax, dword ptr[hdc]
		push eax
		call CreateCompatibleDC
		mov esp, dword ptr[x1]
		mov  dword ptr[hdcMem], eax
		mov  dword ptr[x], 0
		mov  dword ptr[y], 0
		// for (int i = 0; i < MAP_HEIGHT; i++)
		mov  ebx, -1
		mov  esi, 0
		Loopoutside:
		add  ebx, 1
			cmp  ebx, MAP_HEIGHT  // ebxΪi
			jnl  Endup
			mov  esi, MAP_WIDTH - 1 // esiΪj
			Loopinside :
			cmp  esi, 0
			jl   Loopoutside
			// x = j * 40 + 20
			imul eax, esi, 28h
			add  eax, 14h
			mov  dword ptr[x], eax
			// y = i * 40 + 41;
			imul eax, ebx, 28h
			add  eax, 29h
			mov  dword ptr[y], eax
			// �ȼ��� map_type[i][j]��ֵ�������ж� 3Ch= 4*15���ֽ�
			imul eax, ebx, 3Ch
			add  eax, dword ptr[this]
			// if map_type[i][j] == B_H_

			cmp  dword ptr[eax + esi * 4], 4
			je   R_H_Label
			cmp  dword ptr[eax + esi * 4], 5
			je   Y_H_Label
			cmp  dword ptr[eax + esi * 4], 6
			je   B_H_Label
			cmp  dword ptr[eax + esi * 4], 7
			je   TreeLabel
			cmp  dword ptr[eax + esi * 4], 8
			je   WindLabel
			sub  esi, 1
			jmp  Loopinside
			R_H_Label :
		// ����SelectObject(hdcMem,m_bitmap_redHouse)��������ջ��˳���������
		mov  eax, dword ptr[this]
			mov  ecx, dword ptr[eax + 314h]
			push ecx
			mov  edx, dword ptr[hdcMem]
			push edx
			call SelectObject
			// ����TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255))��ͬ�����ε�˳���������
			push 0FF00FFh
			push 11h
			push 28h
			push 0
			push 0
			mov  eax, dword ptr[hdcMem]
			push eax
			push 11h
			push 28h
			mov  ecx, dword ptr[y]
			sub  ecx, 11h
			push ecx
			mov  edx, dword ptr[x]
			push edx
			mov  eax, dword ptr[hdc]
			push eax
			call TransparentBlt
			sub  esi, 1
			mov esp, dword ptr[x1]
			jmp  Loopinside
			Y_H_Label :
		// ����SelectObject(hdcMem,m_bitmap_yellowHouse)��������ջ��˳���������
		mov  eax, dword ptr[this]
			mov  ecx, dword ptr[eax + 31Ch]
			push ecx
			mov  edx, dword ptr[hdcMem]
			push edx
			call SelectObject
			// ����TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255))��ͬ�����ε�˳���������
			push 0FF00FFh
			push 11h
			push 28h
			push 0
			push 0
			mov  eax, dword ptr[hdcMem]
			push eax
			push 11h
			push 28h
			mov  ecx, dword ptr[y]
			sub  ecx, 11h
			push ecx
			mov  edx, dword ptr[x]
			push edx
			mov  eax, dword ptr[hdc]
			push eax
			call TransparentBlt
			sub  esi, 1
			mov esp, dword ptr[x1]
			jmp  Loopinside
			B_H_Label :
		// ����SelectObject(hdcMem,m_bitmap_blueHouse)��������ջ��˳���������
		mov  eax, dword ptr[this]
			mov  ecx, dword ptr[eax + 328h]
			push ecx
			mov  edx, dword ptr[hdcMem]
			push edx
			call SelectObject
			// ����TransparentBlt(hdc,x,y-17,40,17,hdcMem,0,0,40,17,RGB(255,0,255))��ͬ�����ε�˳���������
			push 0FF00FFh
			push 11h
			push 28h
			push 0
			push 0
			mov  eax, dword ptr[hdcMem]
			push eax
			push 11h
			push 28h
			mov  ecx, dword ptr[y]
			sub  ecx, 11h
			push ecx
			mov  edx, dword ptr[x]
			push edx
			mov  eax, dword ptr[hdc]
			push eax
			call TransparentBlt
			sub  esi, 1
			mov esp, dword ptr[x1]
			jmp  Loopinside
			TreeLabel :
		// ����SelectObject(hdcMem,m_bitmap_Tree)��������ջ��˳���������
		mov  eax, dword ptr[this]
			mov  ecx, dword ptr[eax + 320h]
			push ecx
			mov  edx, dword ptr[hdcMem]
			push edx
			call SelectObject
			// ����TransparentBlt(hdc,x,y-27,40,27,hdcMem,0,0,40,27,RGB(255,0,255))��ͬ�����ε�˳���������
			push 0FF00FFh
			push 1Bh
			push 28h
			push 0
			push 0
			mov  eax, dword ptr[hdcMem]
			push eax
			push 1Bh
			push 28h
			mov  ecx, dword ptr[y]
			sub  ecx, 1Bh
			push ecx
			mov  edx, dword ptr[x]
			push edx
			mov  eax, dword ptr[hdc]
			push eax
			call TransparentBlt
			sub  esi, 1
			mov esp, dword ptr[x1]
			jmp  Loopinside
			WindLabel :
		// ����SelectObject(hdcMem,m_bitmap_windUp)��������ջ��˳���������
		mov  eax, dword ptr[this]
			mov  ecx, dword ptr[eax + 32Ch]
			push ecx
			mov  edx, dword ptr[hdcMem]
			push edx
			call SelectObject
			// ����TransparentBlt(hdc,260,161,120,118,hdcMem,(1-m_nShowID)*120,0,120,118,RGB(255,0,255))��ͬ�����ε�˳���������
			push 0FF00FFh
			push 76h
			push 78h
			push 0
			mov  eax, dword ptr[this]
			mov  ecx, 1
			sub  ecx, dword ptr[eax + 30Ch]
			// ecx * 78h ���������edx��
			imul edx, ecx, 78h
			push edx
			mov  eax, dword ptr[hdcMem]
			push eax
			push 76h
			push 78h
			push 0A1h
			push 104h
			mov  ecx, dword ptr[hdc]
			push ecx
			call TransparentBlt
			sub  esi, 1
			mov esp, dword ptr[x1]
			jmp  Loopinside
			Endup :
		// DeleteDC(hdcMem);
		mov  eax, dword ptr[hdcMem]
			push eax
			call DeleteDC
			mov esp, dword ptr[x1]
	}
}


void CGameMap::MapBlast(int i, int j, int power)
{
	__asm {
		mov  ebx, dword ptr[power]
		cmp  ebx, 1
		je   C1
		cmp  ebx, 2
		je   C2
		cmp  ebx, 3
		je   C3
		cmp  ebx, 4
		je   C4
		jmp  C1
		C1 :
		mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_One
			jmp  End
			C2 :
		mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_One
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Two
			jmp  End
			C3 :
		mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_One
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Two
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Three
			jmp  End
			C4 :
		mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_One
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Two
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Three
			mov  eax, dword ptr[j]
			push eax
			mov  ecx, dword ptr[i]
			push ecx
			mov  ecx, dword ptr[this]
			call CGameMap::BlastBlock_Four
			End :
	}
}

void CGameMap::BlastBlock_One(int i, int j)
{
	int ptr1 = (int)map_type;
	_asm {
		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax

		// �����ʼi�� j
		mov edx, i
		mov ecx, j
		// ����ƫ�ƣ�Ҳ������һ�����ݵ���������λ��i+1
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2
		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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
		// ��ʼ�жϸ�λ���Ƿ�����Ϊ��
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// �ÿ�
		mov dword ptr[eax], 0

		P2:
		mov edx, i
			mov ecx, j
			cmp edx, 0
			jng P3
			// ����ƫ��i-1
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
			// ����ƫ��j+1
			add ecx, 1
			push edx
			// ���������ַ
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
			// ����ƫ��j-1
			sub ecx, 1
			push edx
			// ���������ַ
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

void CGameMap::BlastBlock_Two(int i, int j)
{
	int ptr1 = (int)map_type;
	_asm {

		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// �����ʼi�� j
		mov edx, i
		mov ecx, j
		// �洢i+1
		add edx, 1
		mov esi, edx
		// ����ƫ�ƣ�Ҳ������һ�����ݵ���������λ��i+2
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2

		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+1,j��λ��
		cmp dword ptr[eax], 3
		ja  P2



		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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
		// ��ʼ�жϸ�λ���Ƿ�����Ϊ��
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// �ÿ�
		mov dword ptr[eax], 0

		P2:
		mov edx, i
			mov ecx, j
			// �洢i-1
			sub edx, 1
			mov esi, edx

			cmp edx, 1
			jng P3
			// ����ƫ��i-2
			sub edx, 1

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-1,j��λ��
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
			// �洢j+1
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+1��λ��
			cmp dword ptr[eax], 3
			ja  P4


			// ����ƫ��j+2
			add ecx, 1
			push edx
			// ���������ַ
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
			// ����j-1
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-1��λ��
			cmp dword ptr[eax], 3
			ja  P5


			// ����ƫ��j-2
			sub ecx, 1
			push edx
			// ���������ַ
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

void CGameMap::BlastBlock_Three(int i, int j)
{
	int ptr1 = (int)map_type;
	_asm {

		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// �����ʼi�� j
		mov edx, i
		mov ecx, j
		// �洢i+1
		add edx, 1
		mov esi, edx
		mov ebx, ptr1
		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+1,j��λ��
		cmp dword ptr[eax], 3
		ja  P2

		// �洢i+2
		add edx, 1
		mov esi, edx

		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+2,j��λ��
		cmp dword ptr[eax], 3
		ja  P2




		// ����ƫ�ƣ�Ҳ������һ�����ݵ���������λ��i+3
		add edx, 1
		mov ebx, ptr1
		cmp edx, MAP_HEIGHT
		jnb P2

		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+3,j��λ��
		cmp dword ptr[eax], 3
		ja  P2



		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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
		// ��ʼ�жϸ�λ���Ƿ�����Ϊ��
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// �ÿ�
		mov dword ptr[eax], 0

		P2:
		mov edx, i
			mov ecx, j
			cmp edx, 2
			jng P3
			// �洢i-1
			sub edx, 1
			mov esi, edx


			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-1,j��λ��
			cmp dword ptr[eax], 3
			ja  P3

			// �洢i-2
			sub edx, 1
			mov esi, edx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-2,j��λ��
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
			// �洢j+1
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+1��λ��
			cmp dword ptr[eax], 3
			ja  P4

			// �洢j+2
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+2��λ��
			cmp dword ptr[eax], 3
			ja  P4


			// ����ƫ��j+3
			add ecx, 1
			push edx
			// ���������ַ
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
			// ����j-1
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-1��λ��
			cmp dword ptr[eax], 3
			ja  P5

			// ����j-2
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-2��λ��
			cmp dword ptr[eax], 3
			ja  P5


			// ����ƫ��j-3
			sub ecx, 1
			push edx
			// ���������ַ
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

void CGameMap::BlastBlock_Four(int i, int j)
{
	int ptr1 = (int)map_type;
	_asm {

		//push edx
		//push ecx
		//push ebx
		//push edi
		//push eax
		//push esi
		// �����ʼi�� j
		mov edx, i
		mov ecx, j
		// �洢i+1
		add edx, 1
		mov esi, edx
		mov ebx, ptr1
		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+1,j��λ��
		cmp dword ptr[eax], 3
		ja  P2

		// �洢i+2
		add edx, 1
		mov esi, edx

		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+2,j��λ��
		cmp dword ptr[eax], 3
		ja  P2


		// ����ƫ�ƣ�Ҳ������һ�����ݵ���������λ��i+3
		add edx, 1
		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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

		// �ж�i+3,j��λ��
		cmp dword ptr[eax], 3
		ja  P2

		// ��i+4��j���ж�
		add edx, 1
		cmp edx, MAP_HEIGHT
		jnb P2

		// ����edx����Ϊ����Ҫʹ�ó˷�
		push edx
		// ���������ַ
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
		// ��ʼ�жϸ�λ���Ƿ�����Ϊ��
		cmp dword ptr[eax], 3
		ja  P2
		cmp dword ptr[eax], 0
		je  P2
		// �ÿ�
		mov dword ptr[eax], 0

		P2:
		mov edx, i
			mov ecx, j
			cmp edx, 3
			jng P3
			// �洢i-1
			sub edx, 1
			mov esi, edx


			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-1,j��λ��
			cmp dword ptr[eax], 3
			ja  P3

			// �洢i-2
			sub edx, 1
			mov esi, edx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-2,j��λ��
			cmp dword ptr[eax], 3
			ja  P3

			// i-3, j
			sub edx, 1
			mov esi, edx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i-3,j��λ��
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
			// �洢j+1
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+1��λ��
			cmp dword ptr[eax], 3
			ja  P4

			// �洢j+2
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+2��λ��
			cmp dword ptr[eax], 3
			ja  P4

			// �洢j+3
			add ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j+3��λ��
			cmp dword ptr[eax], 3
			ja  P4

			// ����ƫ��j+4
			add ecx, 1
			push edx
			// ���������ַ
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
			// ����j-1
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-1��λ��
			cmp dword ptr[eax], 3
			ja  P5

			// ����j-2
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-2��λ��
			cmp dword ptr[eax], 3
			ja  P5
			// ����j-3
			sub ecx, 1
			mov esi, ecx

			// ����edx����Ϊ����Ҫʹ�ó˷�
			push edx
			// ���������ַ
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

			// �ж�i,j-3��λ��
			cmp dword ptr[eax], 3
			ja  P5

			// ����ƫ��j-4
			sub ecx, 1
			push edx
			// ���������ַ
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

void CGameMap::MapShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = MAP_WIDTH - 1; j >= 0; j--)
		{
			x = j * 40 + 20;
			y = i * 40 + 41;

			if (map_type[i][j] == B_H_)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_blueHouse);
				TransparentBlt(hdc, x, y, 40, 40, hdcMem, 0, 17, 40, 40, RGB(255, 0, 255));
			}
			if (map_type[i][j] == R_H_)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_redHouse);
				TransparentBlt(hdc, x, y, 40, 40, hdcMem, 0, 17, 40, 40, RGB(255, 0, 255));
			}
			if (map_type[i][j] == Y_H_)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_yellowHouse);
				TransparentBlt(hdc, x, y, 40, 40, hdcMem, 0, 17, 40, 40, RGB(255, 0, 255));
			}
			if (map_type[i][j] == R_B_)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_redBrick);
				BitBlt(hdc, x, y, 40, 40, hdcMem, 0, 0, SRCCOPY);
			}
			if (map_type[i][j] == Y_B_)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_yellowBrick);
				BitBlt(hdc, x, y, 40, 40, hdcMem, 0, 0, SRCCOPY);
			}
			if (map_type[i][j] == Tree)
			{
				SelectObject(hdcMem, m_bitmap_Tree);
				TransparentBlt(hdc, x, y, 40, 40, hdcMem, 0, 27, 40, 40, RGB(255, 0, 255));
			}
			if (map_type[i][j] == Box)
			{
				SelectObject(hdcMem, m_bitmap_ShadowBlock);
				TransparentBlt(hdc, x - 3, y - 1, 45, 45, hdcMem, 0, 0, 45, 45, RGB(255, 0, 255));
				SelectObject(hdcMem, m_bitmap_Box);
				BitBlt(hdc, x, y, 40, 40, hdcMem, 0, 0, SRCCOPY);
			}
			if (map_type[i][j] == WIND)
			{
				/*	SelectObject(hdcMem,m_bitmap_windUp);
					TransparentBlt(hdc,260,161,120,118,hdcMem,(1-m_nShowID)*120,0,120,118,RGB(255,0,255));*/
				SelectObject(hdcMem, m_bitmap_windDown);
				TransparentBlt(hdc, 260, 279, 120, 42, hdcMem, 0, 0, 120, 42, RGB(255, 0, 255));
			}

		}
	}

	DeleteDC(hdcMem);
}