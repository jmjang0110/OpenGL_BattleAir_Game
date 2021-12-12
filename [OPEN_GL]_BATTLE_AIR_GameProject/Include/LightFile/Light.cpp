#include "Light.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../CameraFile/Camera.h"

CLight::CLight()
{
}

CLight::~CLight()
{
}

void CLight::UpdateViewPos(float fDeltaTime, CCamera* camera)
{
	if (camera != nullptr)
		m_ViewPos = camera->m_cameraPos;

}

void CLight::Update_Light_info_to_glsl()
{
	GLint viewPosition = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "viewPos");
	glUniform3f(viewPosition, m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);
	
	GLint lightPosLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "lightPos");
	glUniform3f(lightPosLocation, m_LightPos.x, m_LightPos.y, m_LightPos.z);

	
	GLint lightColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "lightColor");
	glUniform3f(lightColorLocation, m_LightColor.x, m_LightColor.y, m_LightColor.z);
}

void CLight::UpdateLightPos(glm::vec3 AirplanePos, GLfloat airplane_Angle, glm::vec3 Camerapos)
{
	m_ViewPos = Camerapos;
	//m_LightPos = AirplanePos;


	//m_LightPos.y = 200.0f;
	//m_LightPos.x = 300.0f * cos(glm::radians((airplane_Angle + 90.0f) * -1));
	//m_LightPos.z = 300.0f * sin(glm::radians((airplane_Angle + 90.0f) * -1));


	m_ViewPos = glm::vec3(0.0f,0.0f,0.0f);
	m_LightPos = AirplanePos;
	m_LightPos.y += 1000.0f;

	m_LightPos.x += 1000.0f * cos(glm::radians((airplane_Angle + 90.0f) * -1));
	m_LightPos.z += 1000.0f * sin(glm::radians((airplane_Angle + 90.0f) * -1));



	//m_ViewPos.x += (10.0f * cos(glm::radians(airplane_Angle + 90.0f)));
	//m_ViewPos.z += (10.0f * sin(glm::radians(airplane_Angle + 90.0f)));
	cout << "Light : "<< m_LightPos.x << " " << m_LightPos.y << " " << m_LightPos.z << endl;


}


bool CLight::Init(glm::vec3 LightPos, glm::vec3 LightColor, glm::vec3 ViewPos)
{
	m_LightPos = LightPos;
	m_LightColor = LightColor;
	m_ViewPos = ViewPos;

	return true;
}

void CLight::Input(float fDeltaTime)
{
}

int CLight::Update(float fDeltaTime)
{
	return 0;
}

int CLight::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CLight::Collision(float fDeltaTime)
{
}

void CLight::Render(float fDeltaTime,CCamera* camera)
{
	UpdateViewPos(fDeltaTime, camera);
	Update_Light_info_to_glsl();


}
