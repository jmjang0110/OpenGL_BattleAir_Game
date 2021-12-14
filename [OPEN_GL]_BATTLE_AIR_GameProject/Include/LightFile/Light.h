#pragma once
#include "../HeaderFile/Game.h"


class CLight
{

public:
	CLight();
	~CLight();

private:
	glm::vec3 m_LightPos;
	glm::vec3 m_LightColor;
	glm::vec3 m_ViewPos;


public:
	void UpdateViewPos(float fDeltaTime, class CCamera* camera);
	void Update_Light_info_to_glsl();

	void UpdateLightPos(glm::vec3 AirplanePos, GLfloat airplane_Angle, glm::vec3 Camerapos);
	void UpdateLightPos_Begin(glm::vec3 AirplanePos, GLfloat airplane_Angle, glm::vec3 Camerapos);

public:

	bool Init(glm::vec3 LightPos, glm::vec3 LightColor, glm::vec3 ViewPos);
	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime,class CCamera* camera);					// * ���

};

