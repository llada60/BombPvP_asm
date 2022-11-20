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
	hIns = hInstance;
	static TCHAR szGameName[] = TEXT("BNB");

	srand((unsigned int)time(0));

	//�õ���Ļ�ֱ���
	int CX = GetSystemMetrics(SM_CXSCREEN );
	int CY = GetSystemMetrics(SM_CYSCREEN );

	HBRUSH hBrush = ::CreateSolidBrush(RGB(0, 0, 0));

	//1.��ƴ���
	WNDCLASSEX wndClassEx;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = hInstance;
	wndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(BNB_ICON));
	wndClassEx.hIconSm = NULL;
	wndClassEx.hCursor = LoadCursor( hInstance, NULL);
	wndClassEx.hbrBackground = hBrush;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = szGameName;
	wndClassEx.lpfnWndProc = MyWinProc;

	//2.ע�ᴰ��
	if( !RegisterClassEx(&wndClassEx))
	{
		MessageBox(NULL, TEXT("������ע��ʧ��!"), TEXT("Ӧ�ó������"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//3.��������
	HWND hWnd = CreateWindow(szGameName, "������--TuringTeam", WS_OVERLAPPEDWINDOW, (CX-BG_WIDTH)/2, (CY-BG_HIGHT)/2, BG_WIDTH,BG_HIGHT, NULL, NULL, hInstance, NULL);

	if (NULL == hWnd)
	{
		MessageBox(NULL, TEXT("���ڴ���ʧ��!"), TEXT("Ӧ�ó������"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//4.��ʾ����
	ShowWindow(hWnd,nShowCmd);

	MSG msg;
	//5.��Ϣ
	while(GetMessage(&msg, 0, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	::DeleteObject(hBrush);

	return 0;
}

CGameCtrl* pCtrl = NULL;

LRESULT CALLBACK MyWinProc(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	switch (Msg)
	{
	case WM_CREATE:
		if (CGameCtrl::pfun_create_object == NULL)
		{
			MessageBox(NULL, TEXT("��Ϸ����ʧ��"), TEXT("��ʾ"),MB_OK | MB_ICONERROR);
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			return 0;
		}
		else
		{
			pCtrl = (*CGameCtrl::pfun_create_object)();
			pCtrl->SetHandel(hWnd,hIns);
			pCtrl->OnCreateGame();
		}
		break;
	case WM_PAINT:
		if (pCtrl != NULL)
		{
			pCtrl->OnGameDraw();
		}
		break;
	case WM_KEYDOWN:
		if (pCtrl != NULL)
		{
			pCtrl->OnKeyDown(wparam);
		}
		break;
	case WM_KEYUP:
		if (pCtrl != NULL)
		{
			pCtrl->OnKeyUp(wparam);
		}
	case WM_LBUTTONDOWN:
		if (pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lparam);
			point.y = HIWORD(lparam);
			pCtrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		if (pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lparam);
			point.y = HIWORD(lparam);
			pCtrl->OnLButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		if (pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lparam);
			point.y = HIWORD(lparam);
			pCtrl->OnMouseMove(point);
		}
		break;
	case WM_TIMER:
		if (pCtrl != NULL)
		{
			pCtrl->OnGameRun(wparam);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		delete pCtrl;
		pCtrl = NULL;
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wparam, lparam);
}