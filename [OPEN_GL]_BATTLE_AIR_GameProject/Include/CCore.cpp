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
	return true;
}

void CCore::MyProgramInit()
{
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

GLvoid CCore::MyDrawScene()
{
	return GLvoid();
}

GLvoid CCore::MyTimer(GLint value)
{
	return GLvoid();
}
