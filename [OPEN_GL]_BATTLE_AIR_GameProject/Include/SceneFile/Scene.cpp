#include "Scene.h"
#include "SceneManager.h"
#include "../LightFile/Light.h"
#include "../CameraFile/Camera.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../ObjectFile/AxisFile/Axis.h"

#include "../ObjectFile/AirplaneFile/Airplane.h"
#include "../ObjectFile/MonsterFile/Monster.h"




CScene::CScene()
{
	m_bEnable = false;


}

CScene::~CScene()
{
	if (m_Camera != nullptr)
		delete m_Camera;

	if (m_Light != nullptr)
		delete m_Light;


}

void CScene::UpdateProjectionMat()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_SIZE_WIDTH / (float)WINDOW_SIZE_HEIGHT, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

}

void CScene::UpdateOrthoMat()
{
	glm::mat4 Ortho = glm::mat4(1.0f);
	Ortho = glm::ortho(-1.5f, 1.5f, -1.5f, 1.5f, 0.1f, 50.0f);
	Ortho = glm::translate(Ortho, glm::vec3(0.0, 0.0, -1.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &Ortho[0][0]);

}

bool CScene::Init()
{

	if (m_Camera == nullptr)
	{
		m_Camera = new CCamera;
		m_Camera->Init(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	}

	if (m_Light == nullptr)
	{
		m_Light = new CLight;
		m_Light->Init(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (m_Axis == nullptr)
	{
		m_Axis = new CAxis;
		m_Axis->Init(0.0f);
	}

	
	if (m_Airplane == nullptr)
	{
		m_Airplane = new CAirplane;
		// Init( scale color Pivot FileName )  
		m_Airplane->Init(glm::vec3(1.0f, 1.3f, 0.5f), glm::vec3(255.0f / 255.0f, 153.0f / 255.0f, rand() % 255 / 255.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), "./ObjectFile/AirplaneFile/airplane3.obj");
	}

	if (m_Monster == nullptr)
	{
		m_Monster = new CMonster;
		m_Monster->Init(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(255.0f / 255.0f, 153.0f / 255.0f, rand() % 255 / 255.0f),
			glm::vec3(0.0f, 0.0f, -0.0f), "./ObjectFile/MonsterFile/monster.obj");

	}
	
	


	return true;
}

void CScene::Input(float fDeltaTime)
{

	if (m_Airplane != nullptr)
	{
		m_Airplane->Input(fDeltaTime);
	}

}

int CScene::Update(float fDeltaTime)
{
	if (m_Airplane != nullptr)
	{
		m_Airplane->Update(fDeltaTime);
	}

	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	if (m_Airplane != nullptr)
	{
		m_Airplane->LateUpdate(fDeltaTime);
	}
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
	if (m_Airplane != nullptr)
	{
		m_Airplane->Collision(fDeltaTime);
	}
}

void CScene::Render(float fDeltaTime)
{
	
	
	
	UpdateProjectionMat();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	

	if (m_Camera != nullptr)
		m_Camera->Render(fDeltaTime);

	if (m_Light != nullptr)
		m_Light->Render(fDeltaTime, m_Camera);

	if (m_Axis != nullptr)
		m_Axis->Render(fDeltaTime);


	if (m_Airplane != nullptr)
		m_Airplane->Render(fDeltaTime);

	
	if (m_Monster != nullptr)
		m_Monster->Render(fDeltaTime);




}
