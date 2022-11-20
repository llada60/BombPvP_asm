#include "PlaySound.h"


CPlaySound::CPlaySound()
{
	DeviceID = 0;
	isPlay = false;
	isKeyToStop = false;
}


CPlaySound::~CPlaySound()
{
	// πÿ±’À˘”–MCI
	mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, NULL);
}

void CPlaySound::Play(char *lpstrSoundName)
{
	if (!isKeyToStop)
	{
		m_mciOpen.lpstrDeviceType = "mpegvideo";
		m_mciOpen.lpstrElementName = lpstrSoundName;
		m_mciError = mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&m_mciOpen);

		DeviceID = m_mciOpen.wDeviceID;

		m_mciPlayParms.dwCallback = (DWORD)NULL;
		m_mciPlayParms.dwFrom = (DWORD)0;
		m_mciError = mciSendCommand(DeviceID,MCI_PLAY,0 ,(DWORD)&m_mciPlayParms);

		isPlay = true;
	}
}

void CPlaySound::Stop()
{
	m_mciError = mciSendCommand (DeviceID, MCI_STOP, NULL, NULL);
	m_mciError = mciSendCommand (DeviceID, MCI_CLOSE, NULL, NULL);

	isPlay = false;
}

unsigned long CPlaySound::GetFileLen()
{
	m_mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	m_mciError = mciSendCommand (DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&m_mciStatusParms);
	if(m_mciError)
		return(0);
	return(m_mciStatusParms.dwReturn);
}

unsigned long CPlaySound::GetPos()
{
	m_mciStatusParms.dwItem = MCI_STATUS_POSITION;
	m_mciError = mciSendCommand (DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&m_mciStatusParms);
	if(m_mciError)
		return(0);
	return(m_mciStatusParms.dwReturn);
}

void CPlaySound::setVolume(DWORD vol)
{
	m_mciSetvolume.dwCallback = NULL;
	m_mciSetvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	m_mciSetvolume.dwValue = vol;
	mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&m_mciSetvolume);
}