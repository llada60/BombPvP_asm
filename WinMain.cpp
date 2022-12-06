#include <Windows.h>
#include <time.h>
#include "CGameCtrl.h"
#include "resource.h"

#define BG_WIDTH 815
#define BG_HIGHT 638

HINSTANCE hIns;

PFUN_CREATE_OBJECT CGameCtrl::pfun_create_object = NULL;

LRESULT CALLBACK MyWinProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	static TCHAR szGameName[] = TEXT("BNB");
	static TCHAR szProgramError[] = TEXT("应用程序错误");
	static TCHAR szWindowError[] = TEXT("窗口类注册失败!");
	static TCHAR szWindowName[] = TEXT("BombPvP");
	HBRUSH hBrush;
	WNDCLASSEX wndClassEx;
	HWND hWnd;
	MSG msg;
	_asm {
		// hIns = hInstance;
		mov         eax, dword ptr[hInstance]
		mov         dword ptr[hIns], eax
		// srand((unsigned int)time(0));
		push        0
		call        time
		add         esp, 4
		mov         esi, esp
		push        eax
		call        srand
		add         esp, 4
		//得到屏幕分辨率
		//CX = GetSystemMetrics(SM_CXSCREEN);
		//push		SM_CXSCREEN
		//call		GetSystemMetrics
		//mov         dword ptr[CX], eax
		//CY = GetSystemMetrics(SM_CYSCREEN);
		//push		SM_CYSCREEN
		//call		GetSystemMetrics
		//mov		dword ptr[CY], eax
	}
	//得到屏幕分辨率
	int CX = GetSystemMetrics(SM_CXSCREEN );
	int CY = GetSystemMetrics(SM_CYSCREEN );
	_asm {
		//hBrush = ::CreateSolidBrush(RGB(0, 0, 0));
		push		0
		call		CreateSolidBrush
		mov         dword ptr[hBrush], eax
		// 1.设计窗口
		// wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
		mov			eax, CS_HREDRAW
		or			eax, CS_VREDRAW
		mov         dword ptr[wndClassEx.style], eax
		// wndClassEx.cbSize = sizeof(wndClassEx);
		mov         dword ptr[wndClassEx.cbSize], 30h
		mov         dword ptr[wndClassEx.cbClsExtra], 0
		mov         dword ptr[wndClassEx.cbWndExtra], 0
		// wndClassEx.hInstance = hInstance;
		mov         eax, dword ptr[hInstance]
		mov         dword ptr[wndClassEx.hInstance], eax
		// wndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(BNB_ICON));
		push		BNB_ICON
		mov			eax, dword ptr[hInstance]
		push		eax
		call		LoadIcon
		mov			dword ptr[wndClassEx.hIcon], eax
		mov			dword ptr[wndClassEx.hIconSm], 0
		// wndClassEx.hCursor = LoadCursor( hInstance, NULL);
		push		0
		mov			eax, dword ptr[hInstance]
		push		eax
		call		LoadCursor
		mov			dword ptr[wndClassEx.hCursor], eax
		// wndClassEx.hbrBackground = hBrush;
		mov         eax, dword ptr[hBrush]
		mov			dword ptr[wndClassEx.hbrBackground], eax
		mov			dword ptr[wndClassEx.lpszMenuName], 0
		// wndClassEx.lpszClassName = szGameName;
		mov         dword ptr[wndClassEx.lpszClassName], offset szGameName
		mov         dword ptr[wndClassEx.lpfnWndProc], offset MyWinProc
		// 2.注册窗口
		//if (!RegisterClassEx(&wndClassEx))
		//{
		//	MessageBox(NULL, TEXT("窗口类注册失败!"), TEXT("应用程序错误"), MB_OK | MB_ICONERROR);
		//	return 0;
		//}
		lea         eax, [wndClassEx]
		push		eax
		call		RegisterClassEx
		test		eax, eax
		jne			L1
		mov			ecx, MB_OK
		or			ecx, MB_ICONERROR
		push		ecx
		push        offset szProgramError
		push        offset szProgramError
		push		0
		call		MessageBox
		xor			eax, eax
		jmp			Done
L1:
		//3.创建窗口
		//hWnd = CreateWindow(szGameName, "泡泡堂", WS_OVERLAPPEDWINDOW, (CX - BG_WIDTH) / 2, (CY - BG_HIGHT) / 2, BG_WIDTH, BG_HIGHT, NULL, NULL, hInstance, NULL);
		/*push		0
		mov         eax, dword ptr[hInstance]
		push        eax
		push		0
		push		0
		push		BG_HIGHT
		push		BG_WIDTH
		mov			eax, dword ptr[CY] // CX、CY不太行
		sub			eax, BG_WIDTH
		sar			eax, 1
		push		eax
		mov			eax, dword ptr[CX]
		sub			eax, BG_WIDTH
		sar			eax, 1
		push		eax
		push		WS_OVERLAPPEDWINDOW
		push		offset szWindowName
		push		offset szGameName
		call		CreateWindow
		mov			dword ptr[hWnd], eax
*/
	}

	//3.创建窗口
	hWnd = CreateWindow(szGameName, "BombPvP", WS_OVERLAPPEDWINDOW, (CX-BG_WIDTH)/2, (CY-BG_HIGHT)/2, BG_WIDTH,BG_HIGHT, NULL, NULL, hInstance, NULL);

	_asm {
		//if (NULL == hWnd)
		//{
		//	MessageBox(NULL, TEXT("窗口创建失败!"), TEXT("应用程序错误"), MB_OK | MB_ICONERROR);
		//	return 0;
		//}
		cmp			dword ptr[hWnd], 0
		jne			L2
		mov			ecx, MB_OK
		or			ecx, MB_ICONERROR
		push		ecx
		push        offset szProgramError
		push        offset szProgramError
		push		0
		call		MessageBox
		xor			eax, eax
		jmp			Done
L2:
		// ShowWindow(hWnd,nShowCmd);
		mov         eax, dword ptr[nShowCmd]
		push        eax
		mov         ecx, dword ptr[hWnd]
		push        ecx
		call        ShowWindow
L3:
		// 5.消息
		// while(GetMessage(&msg, 0, 0, 0))
		push		0
		push		0
		push		0
		lea			eax, [msg]
		push		eax
		call		GetMessage
		test		eax, eax
		je			L4
		// ::TranslateMessage(&msg);
		lea         eax, [msg]
		push        eax
		call		TranslateMessage
		// ::DispatchMessage(&msg);
		lea         eax, [msg]
		push        eax
		call		DispatchMessage
		jmp			L3
L4 :
		lea         eax, [hBrush]
		push        eax
		call		DeleteObject
		xor			eax, eax
Done :
	}
}

CGameCtrl* pCtrl = NULL;

LRESULT CALLBACK MyWinProc(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	static TCHAR szGameError[] = TEXT("游戏创建失败");
	static TCHAR szHint[] = TEXT("提示");
	POINT point;
		_asm {
		mov         eax, dword ptr[Msg]
		cmp			eax, WM_CREATE
		je			WmCreate
		cmp			eax, WM_PAINT
		je			WmPaint
		cmp			eax, WM_KEYDOWN
		je          WmKeydown
		cmp			eax, WM_KEYUP
		je			WmKeyup
		cmp			eax, WM_LBUTTONDOWN
		je			WmLbuttondown
		cmp			eax, WM_LBUTTONUP
		je			WmLbuttonup
		
		cmp			eax, WM_MOUSEMOVE
		je			WmMousemove
		cmp			eax, WM_TIMER
		je			WmTimer
		cmp			eax, WM_CLOSE
		je			WmClose
		cmp			eax, WM_DESTROY
		je			WmDestroy
		jmp			Done
WmCreate:
		// if (CGameCtrl::pfun_create_object == NULL)
		cmp         dword ptr[CGameCtrl::pfun_create_object], 0
		jne			CreateNeq
		// MessageBox(NULL, TEXT("游戏创建失败"), TEXT("提示"),MB_OK | MB_ICONERROR);
		mov			eax, MB_OK
		or			eax, MB_ICONERROR
		push		eax
		push		offset szHint
		push		offset szGameError
		push		0
		call		MessageBox
		// DestroyWindow(hWnd);
		mov			eax, dword ptr[hWnd]
		push		eax
		call		DestroyWindow
		// PostQuitMessage(0);
		push		0
		call		PostQuitMessage
		xor			eax, eax
		ret
CreateNeq:
		// pCtrl = (*CGameCtrl::pfun_create_object)();
		call        CGameCtrl::pfun_create_object
		mov         dword ptr[pCtrl], eax
		// pCtrl->SetHandel(hWnd, hIns);
		mov			eax, dword ptr[hIns]
		push		eax
		mov         eax, dword ptr[hWnd]
		push		eax
		mov			ecx, dword ptr[pCtrl]
		call		CGameCtrl::SetHandel
		// pCtrl->OnCreateGame();
		mov			eax, dword ptr[pCtrl]
		mov			edx, dword ptr[eax]
		mov         ecx, dword ptr[pCtrl]
		mov			eax, dword ptr[edx+4]
		call		eax
		jmp			Done // break
WmPaint:
		cmp         dword ptr[pCtrl], 0
		je          WmPaintEq
		// pCtrl->OnGameDraw();
		mov         eax, dword ptr[pCtrl]
		mov         edx, dword ptr[eax]
		mov         ecx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx + 8]
		call        eax
WmPaintEq:
		jmp			Done
WmKeydown:
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmKeydownEq
		// pCtrl->OnKeyDown(wparam);
		mov         eax, dword ptr[wparam]
		push        eax
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[ecx]
		mov         ecx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx + 10h]
		call        eax
WmKeydownEq:
		jmp			Done
WmKeyup:
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmKeyupEq
		// pCtrl->OnKeyUp(wparam);
		mov         eax, dword ptr[wparam]
		push        eax
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[ecx]
		mov         ecx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx + 14h]
		call        eax
WmKeyupEq :
		jmp			Done
WmLbuttondown:
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmLbuttondownEq
		// point.x = LOWORD(lparam);
		mov         eax, dword ptr[lparam]
		and			eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[point], ecx
		// point.y = HIWORD(lparam);
		mov         eax, dword ptr[lparam]
		shr         eax, 10h
		and			eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[ebp-8], ecx // 改！！
		// pCtrl->OnLButtonDown(point);
		mov         eax, dword ptr[ebp - 8] // point.y
		push        eax
		mov         ecx, dword ptr[point]
		push        ecx
		mov         edx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx]
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[eax + 18h]
		call        edx
WmLbuttondownEq:
		jmp			Done
WmLbuttonup:
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmLbuttonupEq
		// point.x = LOWORD(lparam);
		mov         eax, dword ptr[lparam]
		and eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[point], ecx
		// point.y = HIWORD(lparam);
		mov         eax, dword ptr[lparam]
		shr         eax, 10h
		and eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[ebp - 8], ecx // 改！！
		// pCtrl->OnLButtonUp(point);
		mov         eax, dword ptr[ebp - 8] // point.y
		push        eax
		mov         ecx, dword ptr[point]
		push        ecx
		mov         edx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx]
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[eax + 1Ch]
		call        edx
WmLbuttonupEq :
		jmp			Done

WmMousemove:
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmMousemoveEq
		// point.x = LOWORD(lparam);
		mov         eax, dword ptr[lparam]
		and eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[point], ecx
		// point.y = HIWORD(lparam);
		mov         eax, dword ptr[lparam]
		shr         eax, 10h
		and eax, 0FFFFh
		movzx       ecx, ax
		mov         dword ptr[ebp - 8], ecx // 改！！
		// pCtrl->OnMouseMove(point);
		mov         eax, dword ptr[ebp - 8] // point.y
		push        eax
		mov         ecx, dword ptr[point]
		push        ecx
		mov         edx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx]
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[eax + 20h]
		call        edx
WmMousemoveEq :
		jmp			Done
			
WmTimer:		
		// if (pCtrl != NULL)
		cmp         dword ptr[pCtrl], 0
		je          WmTimerEq
		// pCtrl->OnKeyDown(wparam);
		mov         eax, dword ptr[wparam]
		push        eax
		mov         ecx, dword ptr[pCtrl]
		mov         edx, dword ptr[ecx]
		mov         ecx, dword ptr[pCtrl]
		mov         eax, dword ptr[edx + 0Ch]
		call        eax
WmTimerEq :
		jmp			Done
			
WmClose:
		// DestroyWindow(hWnd);
		mov         eax, dword ptr[hWnd]
		push        eax
		call        DestroyWindow
		jmp			Done
			
WmDestroy:
		// delete pCtrl;
		mov         eax, dword ptr[pCtrl]
		mov         dword ptr[ebp - 0D8h], eax
		cmp         dword ptr[ebp - 0D8h], 0
		je          JDestroy
		push        1
		mov         ecx, dword ptr[ebp - 0D8h]
		mov         edx, dword ptr[ecx]
		mov         ecx, dword ptr[ebp - 0D8h]
		mov         eax, dword ptr[edx]
		call        eax
		mov         dword ptr[ebp - 0E0h], eax
		jmp         JDestroy1
JDestroy:
		mov         dword ptr[ebp - 0E0h], 0
JDestroy1:
		// pCtrl = NULL;
		mov         dword ptr[pCtrl], 0
		// PostQuitMessage(0);
		push		0
		call		PostQuitMessage 
	  
Done:
		// return DefWindowProc(hWnd, Msg, wparam, lparam);
		mov         eax, dword ptr[lparam]
		push        eax
		mov         ecx, dword ptr[wparam]
		push        ecx
		mov         edx, dword ptr[Msg]
		push        edx
		mov         eax, dword ptr[hWnd]
		push        eax
		call        DefWindowProc
	}
}
