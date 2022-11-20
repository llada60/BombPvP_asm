/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CPlaySound.h
 *  ��Ҫ����: ��Ϸ��Ч�� ����ͨ��F7���ر�
 *          ���� Play(char* lpstrSoundName)��
 *
 *  ����: ���³�
 *  ��������: 2017��6��5��
 *  ˵��: ��Ч�ļ� �궨���� Sys.h ��
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 
#ifndef CPLAYSOUND_H_
#define CPLAYSOUND_H_

#include "Sys.h"
#include <Mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

class CPlaySound
{
public:
	CPlaySound();
	~CPlaySound();
public:
	void Play(char* lpstrSoundName);  // �򿪲�������Ч�ļ�
	void Stop();                      // �رղ�ֹͣ������Ч�ļ�
	unsigned long GetFileLen();       // ��ȡ�ļ�����
	unsigned long GetPos();           // ��ȡ��ǰ�ļ�����λ��
	void setVolume(DWORD vol);        // ��������

	bool isPlay;         // �Ƿ񲥷ű��λ�����ڲ�����һ����Ч�ر��豸���Ա��´β���
	bool isKeyToStop;    // �Ƿ�F7�ر���Ч��־λ ��ر�Ϊ true
private:
	MCI_OPEN_PARMS m_mciOpen;              // �򿪲���
	MCIERROR m_mciError;                   // ����ָ��
	MCI_PLAY_PARMS m_mciPlayParms;         // ���Ų���
	MCI_STATUS_PARMS m_mciStatusParms;
	MCI_GENERIC_PARMS m_mciclose;          // �ر��豸
	MCI_DGV_SETAUDIO_PARMS m_mciSetvolume; // ���������Ĳ���
	int DeviceID;                          // ��¼���豸ID
};

#endif // !CPLAYSOUND_H_