#pragma once

#include "../../HeaderFile/Game.h"



class CAirplane
{
public:
	CAirplane();
	~CAirplane();


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
	// dir(보고 있는) 위치 // Init에서 초기화
	glm::vec3 m_Dir;
	// Airplane Color 
	glm::vec3 m_Color;
	// Airplane Speed 
	GLfloat m_Speed;

	int m_Turn = 0; // turn == -1 좌측으로 이동중 // 0 == 중지 // 1== 우측으로 이동중

private:
	// collide box [ *** 충돌 박스 *** ]
	class Chexahedron* m_CollideBox;

	

private:
	// 행렬 모음 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);
	// 초기 비행기 생성 시 회전 행렬(변동 x)
	glm::mat4 m_Init_Rotate_Mat = glm::mat4(1.0f);
	
	// 적용할 모델 헹렬의 최종
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

private:
	unsigned int m_texture;

public:
	glm::vec3 GetPivot() { return m_Pivot; }

	glm::vec3 GetDir() { return m_Dir; }

	int GetTurn() { return m_Turn; }
	
	// dir 업데이트 - input에서 사용 
	void Update_Dir(glm::vec3 pivot);

public:
	int loadObj_normalize_center(const char* filename);

public:
	void InitBuffer();

public:
	// ** 이동행렬 반환 함수 **
	glm::mat4 GetTranslateMat() { return m_Translate_Mat; }
	glm::mat4 GetRotateMat() { return m_Rotate_Mat; }
	glm::mat4 GetSacaleMat() { return m_Scale_Mat; }

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

