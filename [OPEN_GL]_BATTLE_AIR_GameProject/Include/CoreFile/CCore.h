#pragma once

#include "../HeaderFile/Game.h"
	// =====================================================
	// < 팀 규칙 > : 모든 클래스는 이 5가지의 기본 함수를 가집니다. 
	//		
	//	 ++ Core 이외의 ' 객 체 ' 는 void Init()까지 
	// 	    총 6개의 기본 함수를 가지도록 약속합니다. 
	// 	    Init 에서의 매개 변수는 자율적으로 가능 
	// =====================================================

class CCore
{


public:
	// 매크로로 정의된 싱글톤 
	DECLARE_SINGLE(CCore);

private:
	RESOLUTION	m_tRS; // 해상도 입니다. ( 창 크기 지정 )
	class CShaderProgramManger* m_ShaderProgramManager = nullptr;

private:
	GLfloat m_fDeltaTime = 0.0f;


public:
	bool Init(int argc, char** argv);
	void Run();

	bool MyProgramInit();
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

