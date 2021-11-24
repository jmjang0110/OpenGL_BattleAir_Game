#include "Timer.h"

DEFINITION_SINGLE(CTimer);


CTimer::CTimer() :
	m_fTimeScale(1.f),
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iFrame(0),
	m_iFrameMax(0)
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrameMax = 60;
	m_iFrame = 0;

	return true;
}

// 업데이트 하면 델타타임이 갱신된다.
void CTimer::Update()
{
	LARGE_INTEGER tTime;

	QueryPerformanceCounter(&tTime);
	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart)
		/ (float)m_tSecond.QuadPart;
	printf("%f\n", m_fDeltaTime);

	//m_fdeltatime_Update = 0.0033333f;

	m_tTime = tTime;
}
