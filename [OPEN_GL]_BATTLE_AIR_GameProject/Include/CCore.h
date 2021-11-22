#pragma once

#include "Game.h"

class CCore
{

private:
	CCore();
	~CCore();

// =====================================================
	// 싱글톤 설정 
private:
	static CCore* m_pInst;
public:

	// 싱글톤 객체를 생성하고 생성되어있다면 
	// 그 고유 객체를 반환하는 함수 입니다.
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}

	// 싱글톤 객체를 delete 하는 함수 입니다. 
	static void DestroyInst()
	{
		if (m_pInst != nullptr)
			delete m_pInst;
		m_pInst = nullptr;

	}
// =====================================================

	// 나중에는 아래 매크로로 싱글톤을 정의할 겁니다. 
	// 지금도 설정 가능인데 일단 파악하기 편하게 이렇게 해놨어요~
//public:
//	DECLARE_SINGLE(CCore);

// =====================================================


public:
	bool Init(int argc, char** argv);
	void Run();

	void MyProgramInit();
	void MyDataDelete();

public:
	void Logic();

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


public:
	GLvoid MyReshape(int width, int height);
	GLvoid MyKeyboard(unsigned char key, int x, int y);
	GLvoid MyMouse(int button, int state, int x, int y);
	GLvoid MyDrawScene();
	GLvoid MyTimer(GLint value);


};

