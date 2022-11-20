/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CPlaySound.h
 *  简要描述: 游戏音效类 可以通过F7键关闭
 *          调用 Play(char* lpstrSoundName)；
 *
 *  作者: 刘新成
 *  创建日期: 2017年6月5日
 *  说明: 音效文件 宏定义在 Sys.h 中
 *
 *  修改日期:
 *  作者:
 *  说明:
 *  当前版本: 1.0
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
	void Play(char* lpstrSoundName);  // 打开并播放音效文件
	void Stop();                      // 关闭并停止播放音效文件
	unsigned long GetFileLen();       // 获取文件长度
	unsigned long GetPos();           // 获取当前文件播放位置
	void setVolume(DWORD vol);        // 设置音量

	bool isPlay;         // 是否播放标记位，用于播放完一个音效关闭设备，以备下次播放
	bool isKeyToStop;    // 是否F7关闭音效标志位 如关闭为 true
private:
	MCI_OPEN_PARMS m_mciOpen;              // 打开参数
	MCIERROR m_mciError;                   // 播放指令
	MCI_PLAY_PARMS m_mciPlayParms;         // 播放参数
	MCI_STATUS_PARMS m_mciStatusParms;
	MCI_GENERIC_PARMS m_mciclose;          // 关闭设备
	MCI_DGV_SETAUDIO_PARMS m_mciSetvolume; // 设置音量的参数
	int DeviceID;                          // 记录打开设备ID
};

#endif // !CPLAYSOUND_H_