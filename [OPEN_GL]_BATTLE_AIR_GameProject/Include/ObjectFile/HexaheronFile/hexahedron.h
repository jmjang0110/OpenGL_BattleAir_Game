#pragma once
#include "../../HeaderFile/Game.h"



// *****************  �� �� ü ************************
class Chexahedron
{
public:
	Chexahedron();
	~Chexahedron();

private:
	class CTriangle* m_Tri[12]{ nullptr };
	glm::vec3 m_Position[8];

	GLfloat m_W = 0.0f;	// ���� 
	GLfloat m_D = 0.0f; // ����
	GLfloat m_H = 0.0f; // ����

private:
	// ��� ���� 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);

	// ������ �� ����� ����
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

	// ������ ����
	glm::vec3 m_Pivot = glm::vec3(1.0f);
	glm::vec3 m_Movedist = glm::vec3(0.0f, 0.0f, 0.0f);
private:
	GLint m_boomDir = 1.0f;
	GLfloat m_BoomAngle = rand() % 180;
	GLfloat m_BoomdDist = 1.0f;


public:
	// idx ��° ���� vec3 ���� ��ȯ - Collide �� ��� 
	glm::vec3 GetCollide_Position(int idx);

public:
	// 3�������� Pivot ���� �������� ����ü ��ǥ���� �����մϴ�. 
	void InitPosition(glm::vec3 Pivot = glm::vec3(0.0f, 0.0f, 0.0f));

public:
	void SetColor(glm::vec3 RGB);
	// ���� ���� ���� 
	void Init(GLfloat W, GLfloat D, GLfloat H, glm::vec3 pivot, stbi_uc* textData3,
		int text_width, int text_height);

	void Update_BoomMotion_translate(float fDeltaTime, glm::vec3 trnaslate);
	void Update_BoomMotion_rotate(float fDeltaTime);



public:
	// ** ��� ������Ʈ �Լ� ** 
	void Update_TranslateForm(glm::vec3 translate);
	void Update_RotateForm(GLfloat Time, GLfloat Axis_x = 0.0f, GLfloat Axis_y = 0.0f, GLfloat Axis_z = 1.0f);
	void Update_ScaleForm(GLfloat sx = 1.0f, GLfloat sy = 1.0f, GLfloat sz = 1.0f);
	void Update_ModelTransform();

	void Render(RENDER_TYPE renderType = RENDER_TYPE::LINE_LOOP);
	

};
