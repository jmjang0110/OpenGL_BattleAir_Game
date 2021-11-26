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
	void UpdateViewPos(glm::vec3 CameraPos);



public:

	bool Init();
	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력

};

