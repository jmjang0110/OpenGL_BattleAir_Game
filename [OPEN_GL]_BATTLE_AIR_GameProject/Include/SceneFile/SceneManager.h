#pragma once

#include "../HeaderFile/Game.h"

// R E A D M E
// ==============================================================
// ** ��� ������ Ŭ���� ** 

// ��� �����ڴ� �� �״�� ������ ��Ʈ�� �մϴ�.

// �ֿ� ����� ����� ��ȯ ���ִ� ���Ұ� �ش� ����� ���� ���ݴϴ�.

// ==============================================================



class CSceneManager
{
public:
	// �̱������� �����մϴ�.
	DECLARE_SINGLE(CSceneManager);


private:
	class CScene * m_Scene_Begin		;		// ���� ����
	class CScene * m_Scene_MainStage	;		// ���� ���� ���� �������� 
	class CScene * m_Scene_End		;		// ���� �� 

private:
	GLboolean m_ChangeStage_Begin_to_Main = false;

public:
	
	// =====================================================
	// �� ��Ģ  : ��� Ŭ������ �� 6������ �⺻ �Լ��� �����ϴ�. 
	// =====================================================

	bool Init();

	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���

	void UpdateChange_Stage();

};

