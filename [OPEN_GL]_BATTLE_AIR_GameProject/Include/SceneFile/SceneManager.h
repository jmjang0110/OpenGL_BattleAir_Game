#pragma once

#include "../HeaderFile/Game.h"

// R E A D M E
// ==============================================================
// ** 장면 관리자 클래스 ** 

// 장면 관리자는 말 그대로 장면들을 컨트롤 합니다.

// 주요 기능은 장면을 전환 해주는 역할과 해당 장면을 실행 해줍니다.

// ==============================================================



class CSceneManager
{
public:
	// 싱글톤으로 선언합니다.
	DECLARE_SINGLE(CSceneManager);


private:
	class CScene * m_Scene_Begin		;		// 게임 시작
	class CScene * m_Scene_MainStage	;		// 실제 게임 구동 스테이지 
	class CScene * m_Scene_End		;		// 게임 끝 

public:
	
	// =====================================================
	// 팀 규칙  : 모든 클래스는 이 6가지의 기본 함수를 가집니다. 
	// =====================================================

	bool Init();

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

