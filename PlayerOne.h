#ifndef CPLAYERONE_H_
#define CPLAYERONE_H_

#include "player.h"

class CPlayerOne : public CPlayer
{
public:
	CPlayerOne();
	virtual ~CPlayerOne();
public:
	virtual void PlayerInit(HINSTANCE hIns);
	virtual void PlayerShow(HDC hdc);
	virtual void PlayerMove(int FX,CGameMap &gameMap,CGameProps &gameProp,CPlaySound &playSound);
	virtual void CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y);
	virtual bool WhetherProp(CGameProps &gameprop);
};

#endif // !CPLAYERONE_H_

