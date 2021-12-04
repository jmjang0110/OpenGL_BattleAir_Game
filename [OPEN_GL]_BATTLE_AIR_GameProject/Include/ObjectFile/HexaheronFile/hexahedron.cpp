#include "hexahedron.h"
#include "../TriangleFile/Triangle.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"



Chexahedron::Chexahedron()
{
}

Chexahedron::~Chexahedron()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_Tri[i] != nullptr)
		{
			delete m_Tri[i];
		}
	}

}

void Chexahedron::InitPosition(glm::vec3 Pivot)
{

	m_Pivot = Pivot;

	m_Position[0] = { Pivot.x - m_W, Pivot.y - m_H, Pivot.z + m_D };
	m_Position[1] = { Pivot.x + m_W, Pivot.y - m_H, Pivot.z + m_D };
	m_Position[2] = { Pivot.x + m_W, Pivot.y - m_H, Pivot.z - m_D };
	m_Position[3] = { Pivot.x - m_W, Pivot.y - m_H, Pivot.z - m_D };
	m_Position[4] = { Pivot.x - m_W, Pivot.y + m_H, Pivot.z + m_D };
	m_Position[5] = { Pivot.x + m_W, Pivot.y + m_H, Pivot.z + m_D };
	m_Position[6] = { Pivot.x + m_W, Pivot.y + m_H, Pivot.z - m_D };
	m_Position[7] = { Pivot.x - m_W, Pivot.y + m_H, Pivot.z - m_D };



}

void Chexahedron::SetColor(glm::vec3 RGB)
{
	for (int i = 0; i < 12; ++i)
	{
		m_Tri[i]->InitColor(RGB.x, RGB.y, RGB.z);

	}

}

void Chexahedron::Init(GLfloat W, GLfloat D, GLfloat H, glm::vec3 pivot,const char* filepath)
{

	m_W = W / 2;
	m_D = D / 2;
	m_H = H / 2;

	InitPosition(pivot);

	for (int i = 0; i < 12; ++i)
		m_Tri[i] = new CTriangle;

	GLfloat R = (rand() / (GLfloat)RAND_MAX) * 0.9f + 0.3f; // 0.0f ~ 1.0f
	GLfloat G = (rand() / (GLfloat)RAND_MAX) * 0.9f + 0.5f; // 0.0f ~ 1.0f
	GLfloat B = (rand() / (GLfloat)RAND_MAX) * 0.9f + 0.2f; // 0.0f ~ 1.0f


	// F R O N T
	glm::vec3 FrontNormal = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Tri[0]->Init(m_Position[4], m_Position[0], m_Position[1],
		R, G, B, FrontNormal, FrontNormal, FrontNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[1]->Init(m_Position[4], m_Position[1], m_Position[5],
		R, G, B, FrontNormal, FrontNormal, FrontNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

	// R I G H T
	glm::vec3 RightNormal = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Tri[2]->Init(m_Position[5], m_Position[1], m_Position[6],
		R, G, B, RightNormal, RightNormal, RightNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[3]->Init(m_Position[6], m_Position[1], m_Position[2],
		R, G, B, RightNormal, RightNormal, RightNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

	// B A C K 
	glm::vec3 backNormal = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Tri[4]->Init(m_Position[3], m_Position[7], m_Position[6],
		R, G, B, backNormal, backNormal, backNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[5]->Init(m_Position[3], m_Position[6], m_Position[2],
		R, G, B, backNormal, backNormal, backNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

	// L E F T 
	glm::vec3 LeftNormal = glm::vec3(-1.0f, 0.0f, 0.0f);
	m_Tri[6]->Init(m_Position[0], m_Position[7], m_Position[3],
		R, G, B, LeftNormal, LeftNormal, LeftNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[7]->Init(m_Position[0], m_Position[4], m_Position[7],
		R, G, B, LeftNormal, LeftNormal, LeftNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

	// U P
	glm::vec3 UpNormal = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Tri[8]->Init(m_Position[7], m_Position[4], m_Position[6],
		R, G, B, UpNormal, UpNormal, UpNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[9]->Init(m_Position[6], m_Position[4], m_Position[5],
		R, G, B, UpNormal, UpNormal, UpNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

	// D O W N
	glm::vec3 DownNormal = glm::vec3(0.0f, -1.0f, 0.0f);

	m_Tri[10]->Init(m_Position[0], m_Position[3], m_Position[1],
		R, G, B, DownNormal, DownNormal, DownNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);
	m_Tri[11]->Init(m_Position[1], m_Position[3], m_Position[2],
		R, G, B, DownNormal, DownNormal, DownNormal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);


}




void Chexahedron::Update_TranslateForm(glm::mat4 airplane_translateMat)
{
	m_Translate_Mat = airplane_translateMat;

}

void Chexahedron::Update_RotateForm(glm::mat4 airplane_RotateMat)
{
	m_Rotate_Mat = airplane_RotateMat;

}

void Chexahedron::Update_ScaleForm(glm::mat4 airplane_ScaleMat)
{
	m_Scale_Mat = airplane_ScaleMat;

}

void Chexahedron::Update_ModelTransform()
{


	m_ModelMatrix_Result = glm::mat4(1.0f);
	m_ModelMatrix_Result = m_Translate_Mat * m_Rotate_Mat * m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));



}

void Chexahedron::Render()
{

	Update_ModelTransform();

	for (int i = 0; i < 12; ++i)
	{
		glLineWidth(2.0f);
		
		if (m_Tri[i] != nullptr)
			m_Tri[i]->Render(RENDER_TYPE::LINE_LOOP);
		
	}


}
