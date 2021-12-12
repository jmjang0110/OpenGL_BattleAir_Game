#include "SoundManager.h"


DEFINITION_SINGLE(CSoundManager);


CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	// 배경화면 사운드 데이터 해제
	FMOD_Sound_Release(m_bgmSound_Begin);
	FMOD_Sound_Release(m_bgmSound_MainStage);
	FMOD_Sound_Release(m_bgmSound_End);
	FMOD_Sound_Release(bgmSound_StageClear);

	// effect 사운드 데이터 해제 
	FMOD_Sound_Release(m_effectSound_Explode);
	
	// 사운드 관련 시스템 해제
	FMOD_System_Release(soundSystem);


}

bool CSoundManager::Init()
{


	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 16, FMOD_INIT_NORMAL, NULL);


	/*FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme1.mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_Begin);*/

	FMOD_System_CreateSound(soundSystem, "./SoundFile/honor-and-sword-main-11222.mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_MainStage);

	/*FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme3_(2).mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_End);

	FMOD_System_CreateSound(soundSystem, "./Sound/MainMenu_Theme.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_StageClear)*/;

	FMOD_System_CreateSound(soundSystem, "./SoundFile/MP_Missle Launch.mp3",
		FMOD_DEFAULT, 0, &m_effectSound_Explode);
	
	
	FMOD_System_CreateSound(soundSystem, "./SoundFile/MP_Mortar Round.mp3",
		FMOD_DEFAULT, 0, &m_effectSound_Explode2);
	//FMOD_System_CreateSound(soundSystem, "./Sound/YouWin.wav",
	//	FMOD_LOOP_NORMAL, 0, &bgmSound_StageClear);


	for (int i = 0; i < 10; ++i)
	{
		FMOD_Channel_SetVolume(m_Explode_Sound_Channel[i], 50.0);
		FMOD_Channel_SetVolume(m_Explode_Sound_Channel2[i], 100);

	}


	// 초기화 동시에 시작 브금을 틉니다. ( 로딩하면서 브금을 트는 효과 )
	//CSoundManager::GetInst()->playSound(SCENE_TYPE::BEGIN);

	//CSoundManager::GetInst()->playSound(SCENE_TYPE::MAIN_STAGE);

	return true;

}

// 종족과 해당스테이지를 인자로 받고 해당하는 사운드  출력
bool CSoundManager::playSound(SCENE_TYPE sceneType)
{
	switch (sceneType)
	{
	case SCENE_TYPE::NONE:
		break;
	case SCENE_TYPE::BEGIN:
		// 시작 시 배경 브금을 틉니다. 
		FMOD_System_PlaySound(soundSystem, m_bgmSound_Begin, NULL, 0, &m_bgmChannel);

		break;
	case SCENE_TYPE::MAIN_STAGE:
		FMOD_System_PlaySound(soundSystem, m_bgmSound_MainStage, NULL, 0, &m_bgmChannel);
		break;
	case SCENE_TYPE::END:
		break;
	default:
		break;
	}
	// 채널 볼륨 설정 
	/*FMOD_Channel_SetVolume(m_effectChannel, 0.4);
	FMOD_Channel_SetVolume(m_effectChannel2, 1.0);
	*/FMOD_Channel_SetVolume(m_bgmChannel, 0.8);
	FMOD_System_Update(soundSystem);
	//while (true)
	//{
	//	FMOD_BOOL isplaying = false;
	//	FMOD_Channel_IsPlaying(m_bgmChannel, &isplaying);
	//	if (isplaying == false)
	//	{
	//		FMOD_System_PlaySound(soundSystem, m_bgmSound_MainStage, NULL, 0, &m_bgmChannel);
	//		break;

	//	}

	//}
	return true;

}

bool CSoundManager::stopSound()
{
	// 사운드 전부를 끕니다. 
	FMOD_Channel_Stop(m_effectChannel);
	FMOD_Channel_Stop(m_bgmChannel);

	for (int i = 0; i < 10; ++i)
		FMOD_Channel_Stop(m_Explode_Sound_Channel[i]);

	return true;

}


bool CSoundManager::playSound_Effect()
{

	//FMOD_System_PlaySound(soundSystem, effectSound_WraithGood, NULL, 0, &m_effectChannel);

	return true;

}

bool CSoundManager::playSound_Effect_Explode(int type )
{


	static int Soundidx = 0;

	static int Soundidx2 = 0;
	if (type == 0)
	{
		FMOD_System_PlaySound(soundSystem, m_effectSound_Explode, NULL, 0, &m_Explode_Sound_Channel[Soundidx++]);
	}
	else if (type == 1)
	{
		FMOD_System_PlaySound(soundSystem, m_effectSound_Explode2, NULL, 0, &m_Explode_Sound_Channel2[Soundidx2++]);

	}
	else
		return false;

	FMOD_System_Update(soundSystem);

	if (Soundidx > 9)
		Soundidx = 0;

	if (Soundidx2 > 9)
		Soundidx2 = 0;


	return true;
}

void CSoundManager::Update()
{
	FMOD_BOOL isplaying = false;
	FMOD_Channel_IsPlaying(m_bgmChannel, &isplaying);
	if (isplaying == false)
		FMOD_System_PlaySound(soundSystem, m_bgmSound_MainStage, NULL, 0, &m_bgmChannel);

	//FMOD_System_Update(soundSystem);
	FMOD_System_Update(soundSystem);
}
