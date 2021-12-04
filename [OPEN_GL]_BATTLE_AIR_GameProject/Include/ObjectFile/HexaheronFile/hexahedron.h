#pragma once
#include "../../HeaderFile/Game.h"



// *****************  육 면 체 ************************
class Chexahedron
{
public:
	Chexahedron();
	~Chexahedron();

private:
	class CTriangle* m_Tri[12]{ nullptr };
	glm::vec3 m_Position[8];

	GLfloat m_W = 0.0f;	// 가로 
	GLfloat m_D = 0.0f; // 세로
	GLfloat m_H = 0.0f; // 높이

private:
	// 행렬 모음 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);

	// 적용할 모델 헹렬의 최종
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

	// 기준점 정보
	glm::vec3 m_Pivot = glm::vec3(1.0f);
	glm::vec3 m_Movedist = glm::vec3(0.0f, 0.0f, 0.0f);


public:
	// 3차원상의 Pivot 점을 기준으로 육면체 좌표값를 설정합니다. 
	void InitPosition(glm::vec3 Pivot = glm::vec3(0.0f, 0.0f, 0.0f));

public:
	void SetColor(glm::vec3 RGB);
	// 가로 세로 높이 
	void Init(GLfloat W, GLfloat D, GLfloat H, glm::vec3 pivot, const char* filepath);

public:
	void Update_TranslateForm(glm::mat4 airplane_translateMat);
	void Update_RotateForm(glm::mat4 airplane_RotateMat);
	void Update_ScaleForm(glm::mat4 airplane_ScaleMat);

	void Update_ModelTransform();

	void Render();
	

};
