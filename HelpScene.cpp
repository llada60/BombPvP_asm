#include "HelpScene.h"

void CHelpScene::HelpSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	int x = 0;
	__asm {
		mov  dword ptr[x], esp

		mov  eax, dword ptr[this]
		mov  ecx, dword ptr[eax + 4]
		push ecx
		mov  edx, dword ptr[hdcMem]
		push edx
		call SelectObject
		mov  esp, dword ptr[x]

		push 0CC0020h
		push 0
		push 0
		mov  eax, dword ptr[hdcMem]
		push eax
		push 258h
		push 320h
		push 0
		push 0
		mov  ecx, dword ptr[hdc]
		push ecx
		call BitBlt
		mov  esp, dword ptr[x]

		mov  eax, dword ptr[this]
		movzx ecx, byte ptr[eax]
		test  ecx, ecx
		je    L2
		mov  eax, dword ptr[this]
		mov  ecx, dword ptr[eax+0Ch]
		push ecx
		mov  edx, dword ptr[hdcMem]
		push edx
		call SelectObject
		mov  esp, dword ptr[x]
		jmp  Counti
	L2:
		mov eax, dword ptr[this]
		mov ecx, dword ptr[eax+8]
		push ecx
		mov edx, dword ptr[hdcMem]
		push edx
		call SelectObject
		mov  esp, dword ptr[x]
		jmp Counti
	Counti:
		push 0CC0020h
		push 0
		push 0
		mov  eax, dword ptr[hdcMem]
		push eax
		push 26h
		push 50h
		push 232h
		push 0
		mov  ecx, dword ptr[hdc]
		push ecx
		call BitBlt
		mov  esp, dword ptr[x]

		mov  eax, dword ptr[hdcMem]
		push eax
		call DeleteDC
		mov  esp, dword ptr[x]
	}
}

void CHelpScene::MouseMove(POINT point)
{
	__asm {
		mov eax, dword ptr[point]
		cmp eax, 0
		jle F1
		cmp eax, 50h
		jge F1
		mov eax, dword ptr[ebp+0Ch]
		cmp eax, 232h
		jle F1
		cmp eax, 258h
		jge F1
		mov eax, dword ptr[this]
		mov byte ptr[eax], 1
		jmp End1
	F1:
		mov eax, dword ptr[this]
		mov byte ptr[eax], 0
	End1:
	}
}
CHelpScene::CHelpScene()
{
	m_bitmap_help = NULL;
	m_bitmap_return = NULL;
	m_bitmap_return_select = NULL;
	m_isSelect = false;
}
CHelpScene::~CHelpScene()
{
	DeleteObject(m_bitmap_help);
	DeleteObject(m_bitmap_return);
	DeleteObject(m_bitmap_return_select);
	m_bitmap_help = NULL;
	m_bitmap_return = NULL;
	m_bitmap_return_select = NULL;
}
void CHelpScene::HelpSceneInit(HINSTANCE hIns)
{
	m_bitmap_help = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_HELP_BACK));
	m_bitmap_return = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_RETURN));
	m_bitmap_return_select = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_RETURN_SELECT));
}