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

public:

	bool Init(glm::vec3 LightPos, glm::vec3 LightColor, glm::vec3 ViewPos);
	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime,class CCamera* camera);					// * 출력

};

