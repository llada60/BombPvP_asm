/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CMainScene.h
 *  ��Ҫ����: �������࣬��Ϸ����Ĭ�ϳ���
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
#ifndef CMAINSCENE_H_
#define CMAINSCENE_H_

#include "Sys.h"

/*
** �����������ҳѡ���ѡ�С������ڵ�����Ϸ��������˫����Ϸ�������ڰ������������˳�
*/
enum SeclectNum { NO, TWO_GAME, HELP_GAME, QUIT_GAME };

class CMainScene
{
public:
	CMainScene();
	~CMainScene();
public:
	void MainSceneInit(HINSTANCE hIns);
	void MainSceneShow(HDC hdc);

	// �������λ�� �� m_seclectNum �޸ĳ���Ӧֵ ��Ǵ����ĸ�ѡ��
	void MouseMove(POINT point);

	// �������������ĸ�ѡ��
	SeclectNum m_seclectNum;
private:
	HBITMAP m_bitmap_mainBack;
	HBITMAP m_bitmap_twoGame;
	HBITMAP m_bitmap_gameHelp;
	HBITMAP m_bitmap_quitGame;
	HBITMAP m_bitmap_twoGame_in;
	HBITMAP m_bitmap_gameHelp_in;
	HBITMAP m_bitmap_quitGame_in;
};

#endif // !CMAINSCENE_H_

