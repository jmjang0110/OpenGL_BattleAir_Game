#pragma once

#include "../../HeaderFile/Game.h"



//		** ** ** ** **	** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **
//		** F L O O R ** ** F L O O R *** F L O O R *** F L O O R *** F L O O R *** F L O O R *** F L O O R *** F L O O R *** F L O O R ** 
//		** ** ** ** **	** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **** ** ** ** **
//			바 닥 

class CFloor
{
public:
	CFloor();
	~CFloor();


private:
	glm::vec3 m_Position[4];
	glm::vec3 m_Colors[4];
	GLuint m_Index[4] = { 0,1,2,3 };

private:
	class CTriangle* m_Tri[2]; 
	GLfloat m_Floor_Size = 500.0f;

private:
	// 행렬 모음 
	glm::mat4 m_Translate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Rotate_Mat = glm::mat4(1.0f);
	glm::mat4 m_Scale_Mat = glm::mat4(1.0f);
	// 적용할 모델 헹렬의 최종
	glm::mat4 m_ModelMatrix_Result = glm::mat4(1.0f);

public:
	GLfloat GetSize() { return m_Floor_Size; };

public:
	void Init(stbi_uc* textData,
		int text_width, int text_height);
	
public:
	void Update_TranslateForm(GLfloat dx = 0.0f, GLfloat dy = 0.0f, GLfloat dz = 0.0f);
	void Update_RotateForm(GLfloat Time, GLfloat Axis_x = 0.0f, GLfloat Axis_y = 0.0f, GLfloat Axis_z = 1.0f);
	void Update_ScaleForm(GLfloat sx = 1.0f, GLfloat sy = 1.0f, GLfloat sz = 1.0f);
	
	void Update_ModelTransform();
		
public:
	void InitPosition();
	void InitColor();
	
	void Render();



};
