#include "Bullet.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../../HeaderFile/stb_image.h"
#include "../HexaheronFile/hexahedron.h"
#include "../BulletFile/BulletList.h"
#include "../TriangleFile/Triangle.h"
#include "../../SoundFile/SoundManager.h"


CBulletList::CBulletList()
{

}

CBulletList::~CBulletList()
{
	EraseAll();
	delete m_pBegin;
	delete m_pEnd;

}


void CBulletList::Init(stbi_uc* textData2, int text_width, int text_height)
{


	for (int i = 0; i < 10; ++i)
	{
		m_tri[i] = new CTriangle;
		glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
		//m_tri[i]->Init(0.5f,0.5f,0.5f,glm::vec3(0.0f,0.0f,0.0f),textData2, text_width, text_height);
		m_tri[i]->Init(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			1.0f, 1.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), textData2, text_width, text_height);
	}

	m_prototype_bullet = new CBullet;
	m_prototype_bullet->Init(glm::vec3(2.0f / 3, 0.5f / 3, 0.5f / 3), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,0.0f,0.0f),
		"./ObjectFile/BulletFile/Missile.obj", 0.0f,
		m_Bullet_Text_data, m_Bullet_width, m_Bullet_height, m_tri);


	m_Bullet_Text_data = textData2;
	m_Bullet_width = text_width;
	m_Bullet_height = text_height;


	m_pBegin = new NODE;
	m_pEnd = new NODE;

	m_pBegin->pNext = m_pEnd;
	m_pEnd->pNext = NULL;

	m_pBegin->pPrev = NULL;
	m_pEnd->pPrev = m_pBegin;


	m_Count = 0;
}

bool CBulletList::check_crash_dot(glm::vec3 dot, Chexahedron* obj)
{
	

	float x1, x2, y1, y2, z1, z2;

	x1 = obj->GetCollide_Position(3).x;
	y1 = obj->GetCollide_Position(3).y;
	z1 = obj->GetCollide_Position(3).z;

	x2 = obj->GetCollide_Position(5).x;
	y2 = obj->GetCollide_Position(5).y;
	z2 = obj->GetCollide_Position(5).z;

	if (((x1 <= dot.x) && (dot.x <= x2)) && ((y1 <= dot.y) && (dot.y <= y2)) && ((z1 <= dot.z) && (dot.z <= z2))) {
		return true;
	}

	return false;


}

//int CBulletList::Collision(float fDeltatime, POSITION ObjectLT, POSITION ObjectSize)
//{
//
//
//	// 충돌횟수
//	int CollisionCheckNum = 0;
//	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
//	{
//		if (pNode)
//		{
//			// 총알과 해당 객체가 충돌했다면 충돌 갯수를 늘려준다...
//			if (pNode->bullet->Collision(fDeltatime, ObjectLT, ObjectSize))
//			{
//				CollisionCheckNum += 1;
//
//				PNODE delNode = pNode;
//				pNode = pNode->pPrev;
//				Erase(delNode);
//
//			}
//		}
//	}
//
//
//	return CollisionCheckNum;
//
//}


void CBulletList::PushBack(glm::vec3 AirplanePos, GLfloat airplane_Angle)
{
	if (this == nullptr)
		int i = 0;


	PNODE NewNode = new NODE;
	//CBullet* NewBullet = new CBullet;

	//NewBullet = m_prototype_bullet;
	//memcpy(NewBullet, m_prototype_bullet, sizeof(NewBullet));

	//NewBullet = m_prototype_bullet;
	//NewBullet->InitBuffer();
	//NewBullet->Update_airplane_angle(airplane_Angle);
	//NewBullet->Update_airplane_Pos(AirplanePos);

	//NewNode->bullet = NewBullet;

	NewNode->bullet = new CBullet;
	NewNode->bullet->Init(glm::vec3(2.0f / 3, 0.5f / 3, 0.5f / 3), glm::vec3(0.0f, 0.0f, 0.0f), AirplanePos,
		"./ObjectFile/BulletFile/Missile.obj", airplane_Angle, 
		m_Bullet_Text_data, m_Bullet_width,m_Bullet_height, m_tri);
	

	NewNode->pNext = m_pEnd;
	m_pEnd->pPrev->pNext = NewNode;

	NewNode->pPrev = m_pEnd->pPrev;
	m_pEnd->pPrev = NewNode;

	m_Count += 1;

}

//void CBulletList::PushBack(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
//{
//	if (this == nullptr)
//		int i = 0;
//
//
//	PNODE NewNode = new NODE;
//	POSITION BulletSize = { MonsterSize.x,MonsterSize.y };
//	POSITION BulletLTPos = { MonsterLT.x + MonsterSize.x / 2 - BulletSize.x / 2, MonsterLT.y - BulletSize.y };
//
//	NewNode->bullet = new CBullet;
//	NewNode->bullet->Init(BulletLTPos, BulletSize, BulletVector, Speed);
//
//	NewNode->pNext = m_pEnd;
//	m_pEnd->pPrev->pNext = NewNode;
//
//	NewNode->pPrev = m_pEnd->pPrev;
//	m_pEnd->pPrev = NewNode;
//
//	m_Count += 1;
//}

void CBulletList::Erase(PNODE delNode)
{
	if (delNode == nullptr || delNode == m_pEnd || delNode == m_pBegin)
		return;
	PNODE DeleteNode = delNode;

	delNode->pPrev->pNext = delNode->pNext;
	delNode->pNext->pPrev = delNode->pPrev;

	DeleteNode->bullet->~CBullet();
	delete DeleteNode;


	m_Count -= 1;

}

void CBulletList::RenderAll(float fDeltaTime)
{
	m_pBegin;
	m_pEnd;
	int i = 0;


	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
	{
		if (pNode)
			pNode->bullet->Render(fDeltaTime);
	}

}

bool CBulletList::EraseAll()
{
	if (Empty())
		return true;

	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = m_pBegin->pNext)
	{
		PNODE DelNode = pNode;
		m_pBegin->pNext = DelNode->pNext;

		if (DelNode)
		{
			delete DelNode;
			m_Count -= 1;
		}

	}

	if (Empty())
		return true;
	else
		return false;


}

void CBulletList::Update(float fDeltaTime)
{
	// BulletList 내에서 모든 Bullet 의 거리를 이동시킨다...
	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
	{
		if (pNode->bullet)
		{
			//pNode->bullet->Update_Rotate_LR(0.0f, 1.0f, 0.0f);
			pNode->bullet->Update(fDeltaTime);

		}

		if (pNode->bullet->GetEnable() == false)
		{
			PNODE delNode = pNode;
			pNode = pNode->pPrev;
			Erase(delNode);

		}
	}

}

void CBulletList::CheckErase()
{
	
	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
	{
		if (pNode->bullet)
		{
			if (pNode->bullet->GetEnable() == false)
			{
				PNODE delNode = pNode;
				pNode = pNode->pPrev;
				Erase(delNode);

			}
		}
	}


	m_Count -= 1;

}

bool CBulletList::Collision(Chexahedron* obj)
{

	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
	{
		if (pNode->bullet)
		{
			// 미사일과 오브젝트 충돌 O
			if (check_crash_dot(pNode->bullet->GetPivot(), obj) == true && pNode->bullet->GetCollideState() == false)
			{
				pNode->bullet->CollideState_Update(true);
				CSoundManager::GetInst()->playSound_Effect_Explode(1);

			}
		}
	}


	return false;
}


//void CBulletList::Update(float fDeltaTime, _SIZE _size)
//{
//	for (PNODE pNode = m_pBegin->pNext; pNode != m_pEnd; pNode = pNode->pNext)
//	{
//		if (pNode->bullet) {
//			pNode->bullet->SetSize(pNode->bullet->GetSize() + _size);
//			pNode->bullet->SetPos(pNode->bullet->GetPos() - (_size / 2));
//			pNode->bullet->Update(fDeltaTime);
//		}
//
//		if (pNode->bullet->GetEnbale() == false)
//		{
//			PNODE delNode = pNode;
//			pNode = pNode->pPrev;
//			Erase(delNode);
//
//		}
//	}
//}