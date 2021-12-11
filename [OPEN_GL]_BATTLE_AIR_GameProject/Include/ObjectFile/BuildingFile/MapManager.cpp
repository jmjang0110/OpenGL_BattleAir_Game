#include "MapManager.h"
#include "Building1.h"
#include "Building2.h"
#include "Building3.h"

DEFINITION_SINGLE(CMapManager);

CMapManager::CMapManager()
{
}

CMapManager::~CMapManager()
{
}

bool CMapManager::Init(stbi_uc* m_Building1_Text_data, stbi_uc* m_Building2_Text_data, stbi_uc* m_Building3_Text_data, stbi_uc* m_RedPng_Text_data,
	int text_building1_width, int text_building1_height, 
	int text_building2_width, int text_building2_height, 
	int text_building3_width, int text_building3_height, 
	int textRed_height_width, int textRed_height_height)
{
	glm::vec3 Position = glm::vec3(-200.0f, 0.0f, -200.0f);

	for (int i = 0; i < 20; ++i)
	{
		for (int k = 0; k < 20; ++k)
		{
			m_Map[i][k] = rand() % 5;

			switch (m_Map[i][k])
			{
				// ºó°ø°£ 
			case 0:
				Position.x += 5.0f;
				break;

				// building 1
			/*case 1:
				if (m_b1Cnt >= 50)
					break;

				m_Building1[m_b1Cnt] = new CBuilding1;
				m_Building1[m_b1Cnt]->Init(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(1.0f,1.0f,1.0f),
					glm::vec3(Position.x , 3.0f, Position.z), "./ObjectFile/BuildingFile/BrownTown.obj", m_Building1_Text_data, m_RedPng_Text_data,
					text_building1_width, text_building1_height, textRed_height_width, textRed_height_height);
				
				Position.x += 10.0f;
				m_b1Cnt += 1;

				break;*/
			case 1:
			case 2:
			case 4:

				if (m_b2Cnt >= 50)
					break;

				m_Building2[m_b2Cnt] = new CBuilding2;
				m_Building2[m_b2Cnt]->Init(glm::vec3(3.0f, 5.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(Position.x, -3.0f, Position.z), "./ObjectFile/BuildingFile/WindMill.obj", m_Building2_Text_data, m_RedPng_Text_data,
					text_building2_width, text_building2_height, textRed_height_width, textRed_height_height);

				Position.x += 10.0f;
				m_b2Cnt += 1;
				break;
			case 3:
				if (m_b3Cnt >= 50)
					break;

				m_Building3[m_b3Cnt] = new CBuilding3;
				m_Building3[m_b3Cnt]->Init(glm::vec3(15.0f, 3.0f, 15.0f), glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(Position.x, 3.0f, Position.z), "./ObjectFile/BuildingFile/top.obj", m_Building3_Text_data, m_RedPng_Text_data,
					text_building3_width, text_building3_height, textRed_height_width, textRed_height_height);

				Position.x += 10.0f;
				m_b3Cnt += 1;
				break;
			default:
				break;
			}
		}

		Position.z += 10.0f;
		Position.x = 0.0f;

	}

	

	return true;
}

void CMapManager::Input(float fDeltaTime)
{
}

int CMapManager::Update(float fDeltaTime)
{
	return 0;
}

int CMapManager::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CMapManager::Collision(float fDeltaTime)
{
}

void CMapManager::Render(float fDeltaTime)
{

	// Building 1 Render 
	for (int i = 0; i < m_b1Cnt; ++i)
	{
		if (m_Building1[i] != nullptr)
			m_Building1[i]->Render(fDeltaTime);

	}
	for (int i = 0; i < m_b2Cnt; ++i)
	{
		if (m_Building2[i] != nullptr)
			m_Building2[i]->Render(fDeltaTime);

	}
	for (int i = 0; i < m_b2Cnt; ++i)
	{
		if (m_Building3[i] != nullptr)
			m_Building3[i]->Render(fDeltaTime);

	}
}
