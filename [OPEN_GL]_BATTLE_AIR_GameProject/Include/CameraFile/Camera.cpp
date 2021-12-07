#include "Camera.h"
#include "../ObjectFile/AirplaneFile/Airplane.h"
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

	m_View_Mat_Result = m_View; //*m_Translate_Mat* m_Rotate_Mat* m_Scale_Mat;

	unsigned int viewLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "viewTransform"); //--- ºäÀ× º¯È¯ ¼³Á¤
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_View_Mat_Result));

}

void CCamera::UpdateCameraPos(glm::vec3 AirplanePos, GLfloat airplane_Angle)
{
	m_cameraPos = AirplanePos;
	m_cameraPos.y += 1.0f;
	
	m_cameraPos.x += -5.0f * cos(glm::radians((airplane_Angle + 90.0f) * -1));
	m_cameraPos.z += -5.0f * sin(glm::radians((airplane_Angle + 90.0f) * -1));



}

void CCamera::UpdateCameraDirection(GLfloat airplane_Angle)
{
	// vec3(modelTransform * vec4(vPos, 1.0));
	m_cameraDirection = m_cameraPos;

	m_cameraDirection.x = m_cameraPos.x + m_Direction_Length  * cos(glm::radians((airplane_Angle + 90.0f) * -1));
	m_cameraDirection.z = m_cameraPos.z + m_Direction_Length  * sin(glm::radians((airplane_Angle + 90.0f) * -1));
	m_cameraDirection.y = m_cameraPos.y - 1.0f;

	cout << "camera Airplane Angle : " << airplane_Angle << endl;




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
	 
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_cameraPos.x += fDeltaTime * 5.0f;
	}
	
	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_cameraPos.x -= fDeltaTime * 5.0f;
	}
	
	if (GetAsyncKeyState('I') & 0x8000)
	{
		m_cameraPos.y += fDeltaTime * 5.0f;
	}
	
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_cameraPos.y -= fDeltaTime * 5.0f;
	}
	 
	if (GetAsyncKeyState('O') & 0x8000)
	{
		m_cameraPos.z += fDeltaTime * 5.0f;
	}
	
	if (GetAsyncKeyState('P') & 0x8000)
	{
		m_cameraPos.z -= fDeltaTime * 5.0f;
	}
	
}


int CCamera::Update(float fDeltaTime)
{

	UpdateCameraMat(fDeltaTime);

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

}
