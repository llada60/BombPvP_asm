#ifndef CGAMECTRL_H_
#define CGAMECTRL_H_

#include <Windows.h>

#define DECLARE() static CGameCtrl* CreateObject();

#define IMPLEMENT(ThisClass) \
	CGameCtrl* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}\
	Init init##ThisClass(&ThisClass::CreateObject);

class CGameCtrl;

typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();

class CGameCtrl
{
public:
	CGameCtrl() {}
	virtual ~CGameCtrl() {}

public:
	void SetHandel(HWND hWnd, HINSTANCE hIns)
	{
		this->m_hMainWnd = hWnd;
		this->m_hIns = hIns;
	}

	static PFUN_CREATE_OBJECT pfun_create_object;

protected:
	HWND m_hMainWnd;
	HINSTANCE m_hIns;

public:
	virtual void OnCreateGame() {}
	virtual void OnGameDraw() {}
	virtual void OnGameRun(WPARAM nTimerID) {}
	virtual void OnKeyDown(WPARAM nKey) {}
	virtual void OnKeyUp(WPARAM nKey) {}
	virtual void OnLButtonDown(POINT point) {}
	virtual void OnLButtonUp(POINT point) {}
	virtual void OnMouseMove(POINT point) {}
};

class Init
{
public:
	Init(PFUN_CREATE_OBJECT pfn)
	{
		CGameCtrl::pfun_create_object = pfn;
	}
};

#endif // !CGAMECTRL_H_
