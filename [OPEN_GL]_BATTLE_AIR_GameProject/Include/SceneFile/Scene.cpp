#include "Scene.h"
#include "SceneManager.h"

CScene::CScene()
{
	m_bEnable = false;


}

CScene::~CScene()
{
}

bool CScene::Init()
{
	return false;
}

void CScene::Input(float fDeltaTime)
{

}

int CScene::Update(float fDeltaTime)
{
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
}
