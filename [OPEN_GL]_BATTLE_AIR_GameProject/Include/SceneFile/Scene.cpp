#include "Scene.h"
#include "SceneManager.h"
<<<<<<< Updated upstream
=======
#include "../LightFile/Light.h"
#include "../CameraFile/Camera.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../ObjectFile/AxisFile/Axis.h"

#include "../ObjectFile/AirplaneFile/Airplane.h"
#include "../ObjectFile/Monster/Monster.h"


>>>>>>> Stashed changes

CScene::CScene()
{
	m_bEnable = false;


}

CScene::~CScene()
{
}

bool CScene::Init()
{
<<<<<<< Updated upstream
	return false;
=======

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

		m_Monster->Init(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 
			glm::vec3(0.0, 0.0, -5.0f), "./ObjectFile/Monster/monster.obj");
	}
	
	


	return true;
>>>>>>> Stashed changes
}

void CScene::Input(float fDeltaTime)
{

<<<<<<< Updated upstream
=======
	if (m_Airplane != nullptr)
	{
		m_Airplane->Input(fDeltaTime);
	}


	if (m_Monster != nullptr)
	{
		m_Monster->Input(fDeltaTime);

	}
>>>>>>> Stashed changes
}

int CScene::Update(float fDeltaTime)
{
<<<<<<< Updated upstream
=======
	if (m_Airplane != nullptr)
	{
		m_Airplane->Update(fDeltaTime);
	}

	if (m_Monster != nullptr)
	{
		m_Monster->Update(fDeltaTime);
	}

>>>>>>> Stashed changes
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
}

void CScene::Render(float fDeltaTime)
{
<<<<<<< Updated upstream
=======
	
	
	
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


	// monster
	if (m_Monster != nullptr)
		m_Monster->Render(fDeltaTime);

	
	



>>>>>>> Stashed changes
}
