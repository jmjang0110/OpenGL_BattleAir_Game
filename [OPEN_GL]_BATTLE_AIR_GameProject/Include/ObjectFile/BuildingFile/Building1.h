#pragma once

#include "../../HeaderFile/Game.h"



class CBuilding1
{
public:
	CBuilding1();
	~CBuilding1();


	// ==========================
	//obj ���� ���� ������...
	// ==========================
private:
	static std::vector< glm::vec3 > m_outvertex;	// ����			����Ʈ
	static std::vector< glm::vec3 > m_outnormal;	// ��������		����Ʈ
	static std::vector< glm::vec2 > m_outuv;		// �ؽ�ó uv	����Ʈ

	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3 > temp_normals;
	std::vector< glm::vec2 > temp_uvs;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

private:
	static GLint* m_Tri_Num2;	// �ﰢ�� ���� 
	static GLint m_Tri_Num;

private:
	float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
	float aveX, aveY, aveZ;
	float scaleX, scaleY, scaleZ;
	float minX = 0.0, minY = 0.0, minZ = 0.0;
	float maxX = 0.0, maxY = 0.0, maxZ = 0.0;
	float scaleAll;
	// ==========================
	// ==========================

private:
	GLuint m_VAO;
	GLuint m_VBO[3];

private:
	// ���� ��ġ
	glm::vec3 m_Pivot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Color;

public:
	// collide box [ *** �浹 �ڽ� *** ]
	class Chexahedron* m_CollideBox;

private:
	stbi_uc* m_Building1_Text_data = NULL;

public:
	glm::vec3 GetCollide_Position(int idx);

private:
	// ��� ���� 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);
	// ������ �� ����� ����
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

private:
	unsigned int m_texture;

public:
	glm::vec3 GetPivot() { return m_Pivot; }

public:
	int loadObj_normalize_center(const char* filename);

public:
	void InitBuffer();

public:
	// ** ��� ������Ʈ �Լ� ** 
	void Update_TranslateForm(glm::vec3 translate);
	void Update_RotateForm(GLfloat Time, GLfloat Axis_x = 0.0f, GLfloat Axis_y = 0.0f, GLfloat Axis_z = 1.0f);
	void Update_ScaleForm(GLfloat sx = 1.0f, GLfloat sy = 1.0f, GLfloat sz = 1.0f);
	// ** ��� ���� �Լ� ** 
	void Update_ModelTransform(float fDeltaTime);
	void InitTexture_1(stbi_uc* textData, int text_building_width, int text_building_height);


public:
	void Init(glm::vec3 scaleInfo, glm::vec3 color, glm::vec3 pivot, const char* filename, stbi_uc* textData, stbi_uc* textData2,
		int text_building_width, int text_building_heigh, int textRed_height_width, int textRed_height_height);

	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���


};