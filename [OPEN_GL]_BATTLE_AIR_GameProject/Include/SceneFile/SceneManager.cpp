#include "SceneManager.h"
#include "Scene.h"
#include "../SoundFile/SoundManager.h"



DEFINITION_SINGLE(CSceneManager);


CSceneManager::CSceneManager()
{
	m_Scene_Begin = nullptr;
	m_Scene_End = nullptr;
	m_Scene_MainStage = nullptr;


}

CSceneManager::~CSceneManager()
{

	if (m_Scene_Begin == nullptr)
		delete m_Scene_Begin;

	if (m_Scene_MainStage == nullptr)
		delete m_Scene_MainStage;

	if (m_Scene_End == nullptr)
		delete m_Scene_End;


}

bool CSceneManager::Init()
{

	if (m_Scene_Begin == nullptr)
	{
		m_Scene_Begin = new CScene;
		m_Scene_Begin->Init(SCENE_TYPE::BEGIN);
		m_Scene_Begin->SetEnable(true);
	}
	if (m_Scene_MainStage == nullptr)
	{
		m_Scene_MainStage = new CScene;
		m_Scene_MainStage->Init(SCENE_TYPE::MAIN_STAGE);
		//m_Scene_MainStage->SetEnable(true);
	}
	if (m_Scene_End == nullptr)
	{
		m_Scene_End = new CScene;
		m_Scene_End->Init(SCENE_TYPE::END);
	
	}



	return true;

}

void CSceneManager::Input(float fDeltaTime)
{
	// Scene이 활성화 TRUE 인것만 구동합니다. 
	if (m_Scene_Begin->GetEnable() == true)
		m_Scene_Begin->Input(fDeltaTime);
	
	else if (m_Scene_MainStage->GetEnable() == true)
		m_Scene_MainStage->Input(fDeltaTime);
	
	else if (m_Scene_End->GetEnable() == true)
		m_Scene_End->Input(fDeltaTime);



}

int CSceneManager::Update(float fDeltaTime)
{

	if (m_Scene_Begin->GetEnable() == false &&
		m_ChangeStage_Begin_to_Main == false)
	{
		m_Scene_MainStage->SetEnable(true);
		CSoundManager::GetInst()->stopSound();
		CSoundManager::GetInst()->playSound(SCENE_TYPE::MAIN_STAGE);

		m_ChangeStage_Begin_to_Main = true;
	}

	// Scene이 활성화 TRUE 인것만 구동합니다. 
	if (m_Scene_Begin->GetEnable() == true)
		m_Scene_Begin->Update(fDeltaTime);

	else if (m_Scene_MainStage->GetEnable() == true)
		m_Scene_MainStage->Update(fDeltaTime);

	else if (m_Scene_End->GetEnable() == true)
		m_Scene_End->Update(fDeltaTime);

	return 0;
}

int CSceneManager::LateUpdate(float fDeltaTime)
{
	// Scene이 활성화 TRUE 인것만 구동합니다. 
	if (m_Scene_Begin->GetEnable() == true)
		m_Scene_Begin->LateUpdate(fDeltaTime);

	else if (m_Scene_MainStage->GetEnable() == true)
		m_Scene_MainStage->LateUpdate(fDeltaTime);

	else if (m_Scene_End->GetEnable() == true)
		m_Scene_End->LateUpdate(fDeltaTime);

	return 0;
}

void CSceneManager::Collision(float fDeltaTime)
{
	// Scene이 활성화 TRUE 인것만 구동합니다. 
	if (m_Scene_Begin->GetEnable() == true)
		m_Scene_Begin->Collision(fDeltaTime);

	else if (m_Scene_MainStage->GetEnable() == true)
		m_Scene_MainStage->Collision(fDeltaTime);

	else if (m_Scene_End->GetEnable() == true)
		m_Scene_End->Collision(fDeltaTime);


}

void CSceneManager::Render(float fDeltaTime)
{
	// Scene이 활성화 TRUE 인것만 구동합니다. 
	if (m_Scene_Begin->GetEnable() == true)
		m_Scene_Begin->Render(fDeltaTime);

	else if (m_Scene_MainStage->GetEnable() == true)
		m_Scene_MainStage->Render(fDeltaTime);

	else if (m_Scene_End->GetEnable() == true)
		m_Scene_End->Render(fDeltaTime);


}

void CSceneManager::UpdateChange_Stage()
{
}
