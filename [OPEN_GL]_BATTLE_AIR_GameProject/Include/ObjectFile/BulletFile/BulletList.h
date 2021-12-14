#pragma once

#include "../../HeaderFile/Game.h"

// ����� ���Ḯ��Ʈ�� �����մϴ�...
typedef struct _TagNode
{
	class CBullet* bullet = nullptr;
	_TagNode* pNext = nullptr;
	_TagNode* pPrev = nullptr;
}NODE, * PNODE;



class CBulletList
{
private:
	friend class CBullet;

public:
	CBulletList();
	~CBulletList();

private:
	PNODE m_pBegin;
	PNODE m_pEnd;
	int m_Count;


private:
	stbi_uc* m_Bullet_Text_data = NULL;
	int m_Bullet_width = 0, m_Bullet_height = 0;

private:
	float m_fAttack = 100; // �Ѿ� ���ݷ� 
	class CTriangle* m_tri[10];
	class CBullet* m_prototype_bullet;


private:

public:
	// ���ݷ��� ��ȯ�մϴ�. 
	float GetAttack()
	{
		return m_fAttack;

	}
	// ���ݷ��� �����մϴ�...
	void SetAttack(float Attack)
	{
		m_fAttack = Attack;
	}
	void AddAttack()
	{
		m_fAttack += 50.0f;

	}
public:
	void Init(stbi_uc* textData2,int text_width, int text_height);
	bool check_crash_dot(glm::vec3 dot, class Chexahedron* obj);


public:
	// �浹üũ�� ������Ʈ�� ��ġ�� ����� �޽��ϴ�.. ��� �浹 �ߴ����� ��ȯ�մϴ�...
	//int Collision(float fDeltatime, POSITION ObjectLT, POSITION ObjectSize);

public:
	//void PushBack(POSITION playerLT, POSITION playerSize, float Speed);
	void PushBack(glm::vec3 AirplanePos, GLfloat airplane_Angle);	// ����Ʈ�� Bullet �� �߰��մϴ�...
	void Erase(PNODE delNode = nullptr);							// ����Ʈ�� �ش� bullet �� �����մϴ�...

	void RenderAll(float fDeltaTime);								// ���� �Ѿ� ����Ʈ�� ���� ����մϴ�..
	bool EraseAll();												// ���� �Ѿ� ����Ʈ�� ���� �����մϴ�..

	void Update(float fDeltaTime);
	//void Update(float fDeltaTime, _SIZE _size);

	void CheckErase();
	bool Collision(class Chexahedron* obj);
	bool Collision_M1(class CMonster1* obj);
	bool Collision_M2(class CMonster2* obj);
	bool Collision_M3(class CMonster3* obj);
	bool Collision_M4(class CAirballon* obj);

	bool Empty()
	{

		if (this == nullptr)
			return false;

		if (m_Count == 0)
			return true;
		else
			return false;

	}

};

