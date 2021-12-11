#pragma once
#include "../../HeaderFile/Game.h"


class CMonsterManager
{

public:
	// �̱������� �����մϴ�.
	DECLARE_SINGLE(CMonsterManager);

private:
	class CMonster1* m_Monster1[50]{ nullptr };
	class CMonster2* m_Monster2[50]{ nullptr };
	class CMonster3* m_Monster3[50]{ nullptr };


private:
	// ������ ���� ���� 
	GLint m_M1Cnt = 0;
	GLint m_M2Cnt = 0;
	GLint m_M3Cnt = 0;


private:
	GLint m_MonsterMap[50][50];


public:

	// =====================================================
	// �� ��Ģ  : ��� Ŭ������ �� 6������ �⺻ �Լ��� �����ϴ�. 
	// =====================================================

	bool Init(stbi_uc* m_Monster1_Text_data, stbi_uc* m_Monster2_Text_data,
		stbi_uc* m_Monster3_Text_data, stbi_uc* m_RedPng_Text_data,
		int m_Monster1_width, int m_Monster1_height,
		int m_Monster2_width, int m_Monster2_height,
		int m_Monster3_width, int m_Monster3_height,
		int textRed_height_width, int textRed_height_height);


	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���


};

