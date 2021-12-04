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

void CCamera::UPdate_Airplane_Pivot(glm::vec3 air_pivot)
{
	m_cameraPos = air_pivot;
}

void CCamera::UPdate_Camera_Mat_From_Airplane(glm::mat4 trans, glm::mat4 rotate, glm::mat4 scale)
{
	m_Translate_Mat = trans;
	m_Rotate_Mat = rotate;
	m_Scale_Mat = scale;
}

void CCamera::UpdateCameraMat(float fDeltaTime)
{
	m_View = glm::mat4(1.0f);
	m_View = glm::lookAt(m_cameraPos, m_cameraDirection, m_cameraUp);

	m_View_Mat_Result = m_View; //*m_Translate_Mat* m_Rotate_Mat* m_Scale_Mat;

	unsigned int viewLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "viewTransform"); //--- 箔濘 滲�� 撲薑
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_View_Mat_Result));

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
	// x高 + 
	if (GetAsyncKeyState('I') & 0x8000)
	{
		cout << "camer input in" << endl;

		m_cameraPos.x += fDeltaTime * 5.0f;
	}
	// x高 -
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_cameraPos.x -= fDeltaTime * 5.0f;
	}
	// y高 + 
	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_cameraPos.y += fDeltaTime * 5.0f;
	}
	// y高 - 
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_cameraPos.y -= fDeltaTime * 5.0f;
	}
	// Z高 + 
	if (GetAsyncKeyState('O') & 0x8000)
	{
		m_cameraPos.z += fDeltaTime * 5.0f;
	}
	// Z高 - 
	if (GetAsyncKeyState('P') & 0x8000)
	{
		m_cameraPos.z -= fDeltaTime * 5.0f;
	}
	cout << "camer input in" << endl;
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

	UpdateCameraMat(fDeltaTime);



}
