#include "CCore.h"

//DEFINITION_SINGLE(CCore);
CCore* CCore::m_pInst = nullptr;

CCore::CCore()
{

}

CCore::~CCore()
{

}

bool CCore::Init(int argc, char** argv)
{
	// 화면 해상도 지정 ( 창 크기 )
	m_tRS.iW = WINDOW_SIZE_WIDTH;
	m_tRS.iH = WINDOW_SIZE_HEIGHT;
	


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(m_tRS.iW, m_tRS.iH);
	glutCreateWindow("Example5");
	glewExperimental = GL_TRUE;
	glewInit();

	MyProgramInit();


	return true;
}

bool CCore::MyProgramInit()
{
	
	return true;

}

void CCore::MyDataDelete()
{
}

void CCore::Logic()
{
}

void CCore::Input(float fDeltaTime)
{
}

int CCore::Update(float fDeltaTime)
{
	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCore::Collision(float fDeltaTime)
{
}

void CCore::Render(float fDeltaTime)
{


}

void CCore::Run()
{
	glutMainLoop();

}

GLvoid CCore::MyReshape(int width, int height)
{
	return GLvoid();
}

GLvoid CCore::MyKeyboard(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid CCore::MyMouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid CCore::MyDrawScene(float fdeltatime)
{

	Input(fdeltatime);
	Update(fdeltatime);
	LateUpdate(fdeltatime);
	Collision(fdeltatime);
	Render(fdeltatime);


	return GLvoid();
}

GLvoid CCore::MyTimer(GLint value)
{
	return GLvoid();
}
