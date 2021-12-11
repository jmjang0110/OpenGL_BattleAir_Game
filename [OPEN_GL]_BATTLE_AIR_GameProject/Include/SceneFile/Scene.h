#pragma once

#include "../HeaderFile/Game.h"



class CScene
{
private:

	CScene();
	~CScene();

private:
	friend class CSceneManager;


	//private:
		/*
		1. ���� ����
		2. �÷��̾� ����
		3. ���� ���� ����
		*/

private:
	// ( false : ȭ�� ��Ȱ��ȭ , true : ȭ�� Ȱ��ȭ )
	// ȭ�鿡 ���� Ȱ��ȭ ���� �Դϴ�. 
	GLboolean m_bEnable = false;

private:
	class CCamera*	m_Camera;
	class CLight*	m_Light;
	class CLight*	m_Light2;
	class CLight*	m_Light3;
	class CLight*	m_Light4;
	class CAxis*	m_Axis;


// **************************************
// Test For Load OBJ File Render !! 
// **************************************
private:
	class CAirplane* m_Airplane;
	class CAirballon* m_AirBallon;

	class CMonster1* m_Monster1;
	class CMonster2* m_Monster2;
	class CMonster3* m_Monster3;

	class CBackground* m_Background;
	class CBuilding1* m_Building1;
	class CBuilding2* m_Building2;
	class CBuilding3* m_Building3;

	class CFloor* m_Floor[4]; // Floor �� 4�� �����ϰ� �� (1~4)��и鿡 ��ġ 
	class CFloor* m_Floor_test;
	class CTriangle* m_triangle;


	class CBullet* m_Missile;

private:

	stbi_uc* m_Airplane_Text_data = NULL;
	int m_Airplane_width = 0 , m_Airplane_height = 0;

	stbi_uc* m_Bullet_Text_data = NULL;
	int m_Bullet_width = 0, m_Bullet_height = 0;

	stbi_uc* m_RedPng_Text_data = NULL;
	int m_RedPng_width = 0, m_RedPng_height = 0;

	stbi_uc* m_Grass_Text_dtat = NULL;
	int m_Grass_width = 0, m_Grass_height = 0;

	stbi_uc* m_Monster1_Text_data = NULL;
	int m_Monster1_width = 0, m_Monster1_height = 0;

	stbi_uc* m_Monster2_Text_data = NULL;
	int m_Monster2_width = 0, m_Monster2_height = 0;

	stbi_uc* m_Monster3_Text_data = NULL;
	int m_Monster3_width = 0, m_Monster3_height = 0;

	stbi_uc* m_Building1_Text_data = NULL;
	int m_Building1_width = 0, m_Building1_height = 0;

	stbi_uc* m_Building2_Text_data = NULL;
	int m_Building2_width = 0, m_Building2_height = 0;

	stbi_uc* m_Building3_Text_data = NULL;
	int m_Building3_width = 0, m_Building3_height = 0;

	stbi_uc* m_airballon_Text_data = NULL;
	int m_airballon_width = 0, m_airballon_height = 0;

public:
	void InitTexture_All();

public:
	bool check_crash(class Chexahedron* airplane, class Chexahedron* obj);
	bool check_crash_dot(glm::vec3 dot, class Chexahedron* obj);


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
	void UpdateProjectionMat();
	void UpdateOrthoMat();


public:
	void Init_MainStage(SCENE_TYPE type);
	void Init_BeginStage(SCENE_TYPE type);
	void Init_EndStage(SCENE_TYPE type);


	bool Init(SCENE_TYPE type);

	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���


};

