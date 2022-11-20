/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CTwoGameScene.h
 *  ��Ҫ����: ˫����Ϸ������ ˫����Ϸ���������ɸ������
 *
 *  ����: ���³�
 *  ��������: 2017��6��3��
 *  ˵��:
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 
#ifndef CTWOGAMESCENE_H_
#define CTWOGAMESCENE_H_

#include "Sys.h"
#include "GameMap.h"
#include "PlaySound.h"
#include "Bubble.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "GameProps.h"

enum GameStatus { NO_SHOW, START, PLAYER_ONE_WIN, PLAYER_TWO_WIN, DRAW };

class CTwoGameScene
{
public:
	CTwoGameScene();
	~CTwoGameScene();

	// ��ͼ
	CGameMap gameMap;
	// ��Ч
	CPlaySound playSound;
	// ���
	CPlayerOne playerOne;
	CPlayerTwo playerTwo;
	//����
	CGameProps prop;
public:
	void TwoGameSceneInit(HINSTANCE hIns, HWND hWnd);
	void TwoGameSceneShow(HDC hdc);
	void MouseMove(POINT point);
	void OnLButtonDown(HINSTANCE hIns,POINT point);
	void OnKeyDown(WPARAM nKey);
	void OnKeyUp(WPARAM nKey);
	void OnTwoGameRun(WPARAM nTimerID);

	void ChangeBubbleShowID();
	void ChangeBoomShowID();
	void AllBubbleShow(HDC hdc);
	void AllBoomShow(HDC hdc);

	void ShowTime(HDC hdc);         // ����ʱ��ʾ
	void ShowGameStatus(HDC hdc);   // ��Ϸ״̬������ʾ

	void ChangePlayerStartShowID();
	void ChangePropShowID();

	void SetFx(list<CBubble*>::iterator &ite_Bubble, int i, int j); //�����ĸ�������ֵ
	bool IsKillPlayerOne(list<CBubble*>::iterator &ite_Bubble, int i, int j);
	bool IsKillPlayerTwo(list<CBubble*>::iterator &ite_Bubble, int i, int j);
	bool IsButtleBoom(list<CBubble*>::iterator &ite_JBubble, list<CBubble*>::iterator &ite_Bubble);

	void GameOver();
public: 
	/* �������Ƿ��������˳�ѡ���
	** true: ������˳�����
	** false: ���δ���˳�����
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_gameBack;      // ��Ϸ����λͼ
	HBITMAP m_bitmap_road;          // ��Ϸ������·
	HBITMAP m_bitmap_quit;          // �˳�ѡ��λͼ
	HBITMAP m_bitmap_quit_select;   // �˳�ѡ��ѡ��λͼ
	HBITMAP m_bitmap_timeNum;       // ʱ������λͼ
	HBITMAP m_bitmap_statusInfo;    // ��Ϸ״̬��Ϣ��ʾλͼ����ʼ��ʤ����ƽ�֣�ʧ��
	HBITMAP m_bitmap_win_word;      // ��ʾ�ڼ����ʤ������λͼ

	HWND m_twoGameWnd;              // ���ھ��
	HINSTANCE m_twoGameHIns;
	int m_gameTime;                 // ����ʱʱ�� Ĭ������ӣ�300s��
	int m_statusInfo_y;             // ��Ϸ״̬����λ��

	list<CBubble*> m_lstBubble;     // ��������
	list<CBubble*> m_lstBoom;		// ��ը��������

	GameStatus m_gameStatus;        // ö�����ͣ���¼��ʾ��Ϸ״̬���� ��ʼ ʤ�� ƽ�� ʧ��
};

#endif // !CTWOGAMESCENE_H_

