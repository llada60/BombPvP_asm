/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CPlayMusic.h
 *  简要描述: 背景音乐类 播放背景音乐 不同场景音乐不同 可以通过F8键关闭
 *          调用 playMusic(char* music_name);
 *
 *  作者: 刘新成
 *  创建日期: 2017年6月5日
 *  说明: 音乐文件 宏定义在 Sys.h 中
 *
 *  修改日期:
 *  作者:
 *  说明:
 *  当前版本: 1.0
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

