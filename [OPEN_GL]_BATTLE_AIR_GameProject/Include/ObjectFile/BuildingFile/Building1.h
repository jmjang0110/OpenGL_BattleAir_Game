#pragma once

#include "../../HeaderFile/Game.h"



class CBuilding1
{
public:
	CBuilding1();
	~CBuilding1();


	// ==========================
	//obj 파일 관련 변수들...
	// ==========================
private:
	static std::vector< glm::vec3 > m_outvertex;	// 정점			리스트
	static std::vector< glm::vec3 > m_outnormal;	// 법선벡터		리스트
	static std::vector< glm::vec2 > m_outuv;		// 텍스처 uv	리스트

	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3 > temp_normals;
	std::vector< glm::vec2 > temp_uvs;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

private:
	static GLint* m_Tri_Num2;	// 삼각형 개수 
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
	// 현재 위치
	glm::vec3 m_Pivot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Color;


private:
	// 행렬 모음 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);
	// 적용할 모델 헹렬의 최종
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
	// ** 행렬 업데이트 함수 ** 
	void Update_TranslateForm(glm::vec3 translate);
	void Update_RotateForm(GLfloat Time, GLfloat Axis_x = 0.0f, GLfloat Axis_y = 0.0f, GLfloat Axis_z = 1.0f);
	void Update_ScaleForm(GLfloat sx = 1.0f, GLfloat sy = 1.0f, GLfloat sz = 1.0f);
	// ** 행렬 최종 함수 ** 
	void Update_ModelTransform(float fDeltaTime);
	void InitTexture_1();


public:
	void Init(glm::vec3 scaleInfo, glm::vec3 color, glm::vec3 pivot, const char* filename);

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

