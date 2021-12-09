

#include "CoreFile/CCore.h"

// 윈도우 창 화면 색깔 
glm::vec3 g_MainWindowColor = glm::vec3(0.0f, 0.0f, 0.0f);



// =====================================================
// main : Myglut_(Func) : 전역함수로 선언/정의 합니다. 
// =====================================================

GLvoid Myglut_Mouse(int button, int state, int x, int y);
GLvoid Myglut_KeyBoard(unsigned char key, int x, int y);
GLvoid Myglut_Reshape(int width, int height);
GLvoid Myglut_DrawScene();
GLvoid Myglut_Timer(GLint value);

GLvoid MyglutFuncInit();



// =====================================================
// 게임을 초기화 한 후 구동합니다. (Init)->(Run)->(Delete)
// =====================================================
  
int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));



	// *** 게임 초기화 ***
	if (!(CCore::GetInst()->Init(argc, argv)))
	{
		CCore::GetInst()->DestroyInst();
		return 0;

	}

	// *** glut 전역함수 초기화 ***
	MyglutFuncInit();

	// *** 게임 구동 시작 ***
	CCore::GetInst()->Run();

	// *** 게임 데이터 삭제 ***
	CCore::GetInst()->MyDataDelete();
	CCore::GetInst()->DestroyInst();

	return 0;

}


// =====================================================
// Myglut_(Func) 관리 목적으로 존재하는 함수들 입니다...
// 실질적인 구동은 Core 에서 하게 됩니다... 
// 
// 이곳의 정의는 단순히 호출 목적입니다...
// (전역 함수로만 호출 가능)
// =====================================================

GLvoid MyglutFuncInit()
{

	glutDisplayFunc(Myglut_DrawScene);
	glutReshapeFunc(Myglut_Reshape);
	glutMouseFunc(Myglut_Mouse);
	glutKeyboardFunc(Myglut_KeyBoard);
	glutTimerFunc(100, Myglut_Timer, 1);


}

GLvoid Myglut_Mouse(int button, int state, int x, int y)
{
	CCore::GetInst()->MyMouse(button, state, x, y);
	
	glutPostRedisplay();
}

GLvoid Myglut_KeyBoard(unsigned char key, int x, int y)
{
	CCore::GetInst()->MyKeyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid Myglut_Reshape(int width, int height)
{
	CCore::GetInst()->MyReshape(width, height);
	glutPostRedisplay();

}

GLvoid Myglut_DrawScene()
{
	glClearColor(g_MainWindowColor.x, g_MainWindowColor.y, g_MainWindowColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	CCore::GetInst()->MyDrawScene();
	
	glutSwapBuffers();
	return;

}

GLvoid Myglut_Timer(GLint value)
{


	CCore::GetInst()->MyTimer(1);
	glutPostRedisplay();
	glutTimerFunc(1, Myglut_Timer, 1);

}
