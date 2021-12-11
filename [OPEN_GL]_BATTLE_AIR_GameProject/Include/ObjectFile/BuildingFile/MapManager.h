#pragma once
#include "../../HeaderFile/Game.h"


class CMapManager
{

public:
	// �̱������� �����մϴ�.
	DECLARE_SINGLE(CMapManager);

private:
	class CBuilding1* m_Building1[50]{ nullptr };
	class CBuilding2* m_Building2[50]{ nullptr };
	class CBuilding3* m_Building3[50]{ nullptr };


private:
	// ������ �ǹ� ���� 
	GLint m_b1Cnt = 0;
	GLint m_b2Cnt = 0;
	GLint m_b3Cnt = 0;


private:
	GLint m_Map[30][30];


public:

	// =====================================================
	// �� ��Ģ  : ��� Ŭ������ �� 6������ �⺻ �Լ��� �����ϴ�. 
	// =====================================================

	bool Init(stbi_uc* m_Building1_Text_data, stbi_uc* m_Building2_Text_data, 
		stbi_uc* m_Building3_Text_data, stbi_uc* m_RedPng_Text_data,
		int text_building1_width, int text_building1_height,
		int text_building2_width, int text_building2_height,
		int text_building3_width, int text_building3_height,
		int textRed_height_width, int textRed_height_height);


	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���


};

