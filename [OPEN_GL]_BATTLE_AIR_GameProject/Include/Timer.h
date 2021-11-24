#pragma once

#include "Game.h"

// 싱글톤으로 설정합니다. 
class CTimer
{

public:
	DECLARE_SINGLE(CTimer);

	// DeltaTime 을 구하기 위한 변수들
private:
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float			m_fDeltaTime;
	float			m_fTimeScale;
	float			m_fFPS;
	float			m_fFPSTime;
	int				m_iFrameMax;
	int				m_iFrame;


private:
	float m_fdeltatime_Update;


public:
	float GetDeltaTime()const
	{
		return m_fDeltaTime * m_fTimeScale;
	}

	float GetFPS() const
	{
		return m_fFPS;
	}

	float GetTimeScale() const
	{
		return m_fTimeScale;
	}

	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale;
	}

	float GetTimer_Update()
	{
		return m_fdeltatime_Update;

	}


public:
	bool Init();
	void Update();

};