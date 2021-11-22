#include "CCore.h"

GLvoid glut_Mouse(int button, int state, int x, int y)
{
	CCore::GetInst()->MyMouse(button, state, x, y);
	glutPostRedisplay();
}

GLvoid glut_KeyBoard(unsigned char key, int x, int y)
{
	CCore::GetInst()->MyKeyboard(key, x, y);
}

GLvoid glut_Reshape(int width, int height)
{
	CCore::GetInst()->MyReshape(width, height);
}

GLvoid glut_DrawScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();

}

GLvoid glut_Timer(GLint value)
{
	//g_Timer += 5.0f;

	glutPostRedisplay();
	glutTimerFunc(100, glut_Timer, 1);

}