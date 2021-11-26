#include "Camera.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../LightFile/Light.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::UpdateCameraMat(float fDeltaTime)
{
	m_View = glm::mat4(1.0f);
	m_View = glm::lookAt(m_cameraPos, m_cameraDirection, m_cameraUp);

	unsigned int viewLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "viewTransform"); //--- ºäÀ× º¯È¯ ¼³Á¤
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_View));



}

bool CCamera::Init(glm::vec3 CameraPos, glm::vec3 CameraDir, glm::vec3 CameraUp)
{
	m_cameraPos = CameraPos;
	m_cameraDirection = CameraDir;
	m_cameraUp = CameraUp;



	return true;
}

void CCamera::Input(float fDeltaTime)
{
}

int CCamera::Update(float fDeltaTime)
{
	return 0;
}

int CCamera::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCamera::Collision(float fDeltaTime)
{
}

void CCamera::Render(float fDeltaTime)
{

	UpdateCameraMat(fDeltaTime);



}
