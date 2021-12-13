#include "MonsterManager.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Monster3.h"

DEFINITION_SINGLE(CMonsterManager);

CMonsterManager::CMonsterManager()
{
}

CMonsterManager::~CMonsterManager()
{
}

bool CMonsterManager::Init(stbi_uc* m_Monster1_Text_data, stbi_uc* m_Monster2_Text_data,
	stbi_uc* m_Monster3_Text_data, stbi_uc* m_RedPng_Text_data,
	int m_Monster1_width, int m_Monster1_height,
	int m_Monster2_width, int m_Monster2_height,
	int m_Monster3_width, int m_Monster3_height,
	int textRed_height_width, int textRed_height_height)
{
	glm::vec3 Position = glm::vec3(-200.0f, 0.0f, -200.0f);
	
	//COUT << "TEST";
	cout << endl;

	for (int i = 0; i < 20; ++i)
	{
		for (int k = 0; k < 20; ++k)
		{
			m_MonsterMap[i][k] = rand() % 6;

			switch (m_MonsterMap[i][k])
			{
				
			case 1:
			case 4:
				if (m_M1Cnt >= 10)
					break;

				m_Monster1[m_M1Cnt] = new CMonster1;
				m_Monster1[m_M1Cnt]->Init(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(Position.x, rand() % 200, Position.z), "./ObjectFile/MonsterFile/bird.obj", m_Monster1_Text_data, m_RedPng_Text_data,
					m_Monster1_width, m_Monster1_height, textRed_height_width, textRed_height_height);

				Position.x += 50.0f;
				m_M1Cnt += 1;

				break;
			case 0:
			case 2:
				if (m_M2Cnt >= 10)
					break;

				m_Monster2[m_M2Cnt] = new CMonster2;
				m_Monster2[m_M2Cnt]->Init(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
					glm::vec3(Position.x, rand() % 200, Position.z), "./ObjectFile/MonsterFile/Gargoyle_1.obj", m_Monster2_Text_data, m_RedPng_Text_data,
					m_Monster2_width, m_Monster2_height, textRed_height_width, textRed_height_height);

				Position.x += 50.0f;
				m_M2Cnt += 1;
				break;
			case 3:
			case 5:
				if (m_M3Cnt >= 10)
					break;

				m_Monster3[m_M3Cnt] = new CMonster3;
				m_Monster3[m_M3Cnt]->Init(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(Position.x, rand() % 200, Position.z), "./ObjectFile/MonsterFile/monster2.obj", m_Monster3_Text_data, m_RedPng_Text_data,
					m_Monster3_width, m_Monster3_height, textRed_height_width, textRed_height_height);

				Position.x += 50.0f;
				m_M3Cnt += 1;
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

void CMonsterManager::Input(float fDeltaTime)
{
}

int CMonsterManager::Update(float fDeltaTime)
{
	for (int i = 0; i < m_M1Cnt; ++i)
	{
		if (m_Monster1[i] != nullptr)
			m_Monster1[i]->Update(fDeltaTime);

	}
	for (int i = 0; i < m_M2Cnt; ++i)
	{
		if (m_Monster2[i] != nullptr)
			m_Monster2[i]->Update(fDeltaTime);

	}
	for (int i = 0; i < m_M3Cnt; ++i)
	{
		if (m_Monster3[i] != nullptr)
			m_Monster3[i]->Update(fDeltaTime);

	}
	return 0;
}

int CMonsterManager::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CMonsterManager::Collision(float fDeltaTime)
{


}

void CMonsterManager::Render(float fDeltaTime)
{

	// Building 1 Render 
	for (int i = 0; i < m_M1Cnt; ++i)
	{
		if (m_Monster1[i] != nullptr)
			m_Monster1[i]->Render(fDeltaTime);

	}
	for (int i = 0; i < m_M2Cnt; ++i)
	{
		if (m_Monster2[i] != nullptr)
			m_Monster2[i]->Render(fDeltaTime);

	}
	for (int i = 0; i < m_M3Cnt; ++i)
	{
		if (m_Monster3[i] != nullptr)
			m_Monster3[i]->Render(fDeltaTime);

	}
}
