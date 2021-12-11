#pragma once
#include "../../HeaderFile/Game.h"


class CMapManager
{

public:
	// 싱글톤으로 선언합니다.
	DECLARE_SINGLE(CMapManager);

private:
	class CBuilding1* m_Building1[50]{ nullptr };
	class CBuilding2* m_Building2[50]{ nullptr };
	class CBuilding3* m_Building3[50]{ nullptr };


private:
	// 생성된 건물 개수 
	GLint m_b1Cnt = 0;
	GLint m_b2Cnt = 0;
	GLint m_b3Cnt = 0;


private:
	GLint m_Map[30][30];


public:

	// =====================================================
	// 팀 규칙  : 모든 클래스는 이 6가지의 기본 함수를 가집니다. 
	// =====================================================

	bool Init(stbi_uc* m_Building1_Text_data, stbi_uc* m_Building2_Text_data, 
		stbi_uc* m_Building3_Text_data, stbi_uc* m_RedPng_Text_data,
		int text_building1_width, int text_building1_height,
		int text_building2_width, int text_building2_height,
		int text_building3_width, int text_building3_height,
		int textRed_height_width, int textRed_height_height);


	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

