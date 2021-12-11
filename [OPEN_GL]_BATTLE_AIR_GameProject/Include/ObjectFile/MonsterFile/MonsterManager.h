#pragma once
#include "../../HeaderFile/Game.h"


class CMonsterManager
{

public:
	// 싱글톤으로 선언합니다.
	DECLARE_SINGLE(CMonsterManager);

private:
	class CMonster1* m_Monster1[50]{ nullptr };
	class CMonster2* m_Monster2[50]{ nullptr };
	class CMonster3* m_Monster3[50]{ nullptr };


private:
	// 생성된 몬스터 개수 
	GLint m_M1Cnt = 0;
	GLint m_M2Cnt = 0;
	GLint m_M3Cnt = 0;


private:
	GLint m_MonsterMap[50][50];


public:

	// =====================================================
	// 팀 규칙  : 모든 클래스는 이 6가지의 기본 함수를 가집니다. 
	// =====================================================

	bool Init(stbi_uc* m_Monster1_Text_data, stbi_uc* m_Monster2_Text_data,
		stbi_uc* m_Monster3_Text_data, stbi_uc* m_RedPng_Text_data,
		int m_Monster1_width, int m_Monster1_height,
		int m_Monster2_width, int m_Monster2_height,
		int m_Monster3_width, int m_Monster3_height,
		int textRed_height_width, int textRed_height_height);


	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

