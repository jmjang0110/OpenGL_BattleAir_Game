#pragma once

#include "../HeaderFile/Game.h"


class CSoundManager
{

public:
	// 싱글톤으로 관리합니다...
	DECLARE_SINGLE(CSoundManager);

private:
	FMOD_SYSTEM* soundSystem;

	FMOD_SOUND* m_bgmSound_Begin;
	FMOD_SOUND* m_bgmSound_MainStage;
	FMOD_SOUND* m_bgmSound_End;

	FMOD_SOUND* bgmSound_StageClear;

private:
	// 배경 사운드 채널 입니다.  
	FMOD_CHANNEL*	m_bgmChannel;

private:
	// 폭발 / 미사일 발사시 생기는 Effect 사운드 재생 채널 입니다. 
	FMOD_CHANNEL*	m_effectChannel;
	FMOD_SOUND*		m_effectSound_Explode;

private:

	FMOD_CHANNEL* m_Explode_Sound_Channel[10];


public:
	bool Init();

	bool playSound(SCENE_TYPE sceneType);		// 해당씬의 음악을 재생합니다. 
	bool stopSound();							// 배경음악을 중지시킵니다..
	
public:

	bool playSound_Effect();
	bool playSound_Effect_Explode();




};

