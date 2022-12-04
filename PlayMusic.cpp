#include "PlayMusic.h"


CPlayMusic::CPlayMusic()
{
	//isStop = false;
	_asm {
		mov         eax, dword ptr[this]
		mov         byte ptr[eax], 0
	}
}


CPlayMusic::~CPlayMusic()
{
}

void CPlayMusic::PlayBackMusic(char* music_name)
{
	_asm {
		// PlaySound(music_name, NULL, SND_LOOP | SND_ASYNC);
		mov         esi, esp
		push        9
		push        0
		mov         eax, dword ptr[music_name]
		push        eax
		call        PlaySound
		// isStop = false;
		mov         eax, dword ptr[this]
		mov         byte ptr[eax], 0
	}
}

void CPlayMusic::SotpBackMusic()
{
	PlaySound(NULL, NULL, SND_PURGE );
	isStop = true;
}
