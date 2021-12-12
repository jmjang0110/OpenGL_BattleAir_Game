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
	// Airplane Color 
	glm::vec3 m_Color;
	// Airplane Speed 
	GLfloat m_Speed;

private:

	GLfloat m_Angle_LR = 0.0f; // 좌우 각도 
	GLfloat m_Angle_UD = 0.0f; // 상하 각도 

public:
	class Chexahedron* m_CollideBox;

private:
	// collide box [ *** 충돌 박스 *** ]
	stbi_uc* m_Airplane_Text_data = NULL;

private:
	// 행렬 모음 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);
	
	// 적용할 모델 헹렬의 최종
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

	// Angle ( for Updating Move Vector )
	glm::mat4 m_Rotate_Mat_LR = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat_UD = glm::mat4(1.0f);

	// 이동 방향 벡터 입니다. ( 회전에 따른 이동 방향 ) 
	glm::vec3 m_MoveDir_vector = glm::vec3(1.0f, 0.0f, 0.0f);

private:
	unsigned int m_texture;

public:
	glm::vec3 GetPivot() { return m_Pivot; }
	GLfloat GetAngleLR() { return m_Angle_LR; }

public:
	int loadObj_normalize_center(const char* filename);

public:
	void InitBuffer();


private:
	// 플레이어의 총알을 양뱡향 연결리스트로 관리합니다...
	class CBulletList* m_myBulletList;	
	float		    m_LastFireTime = NULL;
	int			m_BulletShotCount;


public:
	class CBulletList* GetBulletList() { return m_myBulletList; }


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
	void InitTexture_1(stbi_uc* textData, int text_airplane_width, int text_airplane_height);


public:
	void Update_Rotate_LR(GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z);
	// CollideBox 의 idx 번째 점의 vec3 값을 반환 - Collide 에 사용 
	glm::vec3 GetCollide_Position(int idx);


public:
	void Init(glm::vec3 scaleInfo, glm::vec3 color, glm::vec3 pivot, const char* filename, stbi_uc* textData, stbi_uc* textData2, stbi_uc* textData3,
		int text_airplane_width, int text_airplane_height, int text_bullet_width, int text_height_width, int textRed_bullet_width, int textRed_height_height);
	

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력


};

