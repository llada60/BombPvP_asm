/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CPlayMusic.h
 *  ��Ҫ����: ���������� ���ű������� ��ͬ�������ֲ�ͬ ����ͨ��F8���ر�
 *          ���� playMusic(char* music_name);
 *
 *  ����: ���³�
 *  ��������: 2017��6��5��
 *  ˵��: �����ļ� �궨���� Sys.h ��
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 
#ifndef CPLAYMUSIC_H_
#define CPLAYMUSIC_H_

#include "Sys.h"
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

class CPlayMusic
{
public:
	CPlayMusic();
	~CPlayMusic();
public:
	void PlayBackMusic(char* music_name);
	void SotpBackMusic();

	bool isStop;
};

#endif // !CPLAYMUSIC_H_

