#pragma once

#include "../HeaderFile/Game.h"


class CSoundManager
{

public:
	// �̱������� �����մϴ�...
	DECLARE_SINGLE(CSoundManager);

private:
	FMOD_SYSTEM* soundSystem;

	FMOD_SOUND* m_bgmSound_Begin;
	FMOD_SOUND* m_bgmSound_MainStage;
	FMOD_SOUND* m_bgmSound_End;

	FMOD_SOUND* bgmSound_StageClear;

private:
	// ��� ���� ä�� �Դϴ�.  
	FMOD_CHANNEL*	m_bgmChannel;

private:
	// ���� / �̻��� �߻�� ����� Effect ���� ��� ä�� �Դϴ�. 
	FMOD_CHANNEL*	m_effectChannel;
	FMOD_SOUND*		m_effectSound_Explode;

private:

	FMOD_CHANNEL* m_Explode_Sound_Channel[10];


public:
	bool Init();

	bool playSound(SCENE_TYPE sceneType);		// �ش���� ������ ����մϴ�. 
	bool stopSound();							// ��������� ������ŵ�ϴ�..
	
public:

	bool playSound_Effect();
	bool playSound_Effect_Explode();




};
