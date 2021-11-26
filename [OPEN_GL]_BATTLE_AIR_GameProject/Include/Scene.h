#pragma once


#include "./HeaderFile/Game.h"


class CScene
{
private:

	CScene();
	~CScene();

private:
	friend class CSceneManager;


//private:
	/*
	1. 몬스터 정보
	2. 플레이어 정보
	3. 지형 정보 저장 
	*/

private:
	// ( false : 화면 비활성화 , true : 화면 활성화 )
	// 화면에 대한 활성화 정보 입니다. 
	GLboolean m_bEnable = false;  
public:
	bool GetEnable()
	{
		return m_bEnable;
	}
	void SetEnable(bool enable)
	{
		m_bEnable = enable;
	}

public:

	bool Init();

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

