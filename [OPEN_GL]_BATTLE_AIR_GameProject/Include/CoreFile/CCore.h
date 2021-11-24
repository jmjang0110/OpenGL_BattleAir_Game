#pragma once

#include "../HeaderFile/Game.h"

class CCore
{

/*
// =====================================================

private:
	CCore();
	~CCore();

	// 싱글톤 설정 
private:
	static CCore* m_pInst;
public:

	 싱글톤 객체를 생성하고 생성되어있다면 
	 그 고유 객체를 반환하는 함수 입니다.
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
*/

public:
	// 매크로로 정의된 싱글톤 
	DECLARE_SINGLE(CCore);

private:
	RESOLUTION	m_tRS; // 해상도 입니다. ( 창 크기 지정 )
	class CShaderProgramManger* m_ShaderProgramManager = nullptr;


public:
	bool Init(int argc, char** argv);
	void Run();

	bool MyProgramInit();
	void MyDataDelete();

public:
	void Logic();

	// =====================================================
	// < 팀 규칙 > : 모든 클래스는 이 5가지의 기본 함수를 가집니다. 
	//		
	//	 ++ Core 이외의 ' 객 체 ' 는 void Init()까지 
	// 	    총 6개의 기본 함수를 가지도록 약속합니다. 
	// 	    Init 에서의 매개 변수는 자율적으로 가능 
	// =====================================================

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

