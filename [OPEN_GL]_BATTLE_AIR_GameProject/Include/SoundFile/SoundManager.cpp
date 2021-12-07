#include "SoundManager.h"


DEFINITION_SINGLE(CSoundManager);


CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	// ���ȭ�� ���� ������ ����
	FMOD_Sound_Release(m_bgmSound_Begin);
	FMOD_Sound_Release(m_bgmSound_MainStage);
	FMOD_Sound_Release(m_bgmSound_End);
	FMOD_Sound_Release(bgmSound_StageClear);

	// effect ���� ������ ���� 
	FMOD_Sound_Release(m_effectSound_Explode);
	
	// ���� ���� �ý��� ����
	FMOD_System_Release(soundSystem);


}

bool CSoundManager::Init()
{


	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, NULL);


	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme1.mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_Begin);

	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme2.mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_MainStage);

	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme3_(2).mp3",
		FMOD_LOOP_NORMAL, 0, &m_bgmSound_End);

	FMOD_System_CreateSound(soundSystem, "./Sound/MainMenu_Theme.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_StageClear);

	FMOD_System_CreateSound(soundSystem, "./Sound/WraithBulletSound.wav",
		FMOD_DEFAULT, 0, &m_effectSound_Explode);

	FMOD_System_CreateSound(soundSystem, "./Sound/YouWin.wav",
		FMOD_LOOP_NORMAL, 0, &bgmSound_StageClear);


	for (int i = 0; i < 10; ++i)
		FMOD_Channel_SetVolume(m_Explode_Sound_Channel[i], 50.0);


	// �ʱ�ȭ ���ÿ� ���� ����� Ƶ�ϴ�. ( �ε��ϸ鼭 ����� Ʈ�� ȿ�� )
	CSoundManager::GetInst()->playSound(SCENE_TYPE::BEGIN);


	return true;

}

// ������ �ش罺�������� ���ڷ� �ް� �ش��ϴ� ����  ���
bool CSoundManager::playSound(SCENE_TYPE sceneType)
{
	switch (sceneType)
	{
	case SCENE_TYPE::NONE:
		break;
	case SCENE_TYPE::BEGIN:
		// ���� �� ��� ����� Ƶ�ϴ�. 
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
	// ä�� ���� ���� 
	FMOD_Channel_SetVolume(m_effectChannel, 1.2);
	FMOD_Channel_SetVolume(m_bgmChannel, 0.8);


	return true;

}

bool CSoundManager::stopSound()
{
	// ���� ���θ� ���ϴ�. 
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

bool CSoundManager::playSound_Effect_Explode()
{

	static int Soundidx = 0;
	FMOD_System_PlaySound(soundSystem, m_effectSound_Explode, NULL, 0, &m_Explode_Sound_Channel[Soundidx++]);

	if (Soundidx > 9)
		Soundidx = 0;

	return true;
}