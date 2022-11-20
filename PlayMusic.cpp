#include "PlayMusic.h"


CPlayMusic::CPlayMusic()
{
	isStop = false;
}


CPlayMusic::~CPlayMusic()
{
}

void CPlayMusic::PlayBackMusic(char* music_name)
{
	PlaySound(music_name, NULL, SND_LOOP |SND_ASYNC );
	isStop = false;
}

void CPlayMusic::SotpBackMusic()
{
	PlaySound(NULL, NULL, SND_PURGE );
	isStop = true;
}
