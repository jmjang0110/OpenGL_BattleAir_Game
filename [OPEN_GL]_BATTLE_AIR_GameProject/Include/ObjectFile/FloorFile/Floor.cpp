#include "Floor.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../TriangleFile/Triangle.h"



CFloor::CFloor()
{
}

CFloor::~CFloor()
{
	if (m_Tri[0] != nullptr)
		delete m_Tri[0];

	if (m_Tri[1] != nullptr)
		delete m_Tri[1];

}

void CFloor::Init(const char* filepath)
{
	m_Tri[0] = new CTriangle;
	m_Tri[1] = new CTriangle;

	InitPosition();
	InitColor();
	GLfloat R = 0.5f; // = (rand() / (GLfloat)RAND_MAX) * 0.9f; // 0.0f ~ 1.0f
	GLfloat G = 1.0f; // = (rand() / (GLfloat)RAND_MAX) * 0.9f; // 0.0f ~ 1.0f
	GLfloat B = 1.0f; //= (rand() / (GLfloat)RAND_MAX) * 0.9f; // 0.0f ~ 1.0f


	glm::vec3 Normal = glm::vec3(1.0f);
	Normal = glm::normalize(glm::cross(m_Position[1] - m_Position[2], m_Position[1] - m_Position[0]));
	
	m_Tri[0]->Init(m_Position[0], m_Position[1], m_Position[2],
		R, G, B, Normal, Normal, Normal,
	glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), filepath);


	Normal = glm::normalize(glm::cross(m_Position[2] - m_Position[3], m_Position[2] - m_Position[0]));
	
	m_Tri[1]->Init(m_Position[0], m_Position[2], m_Position[3],
		R, G, B, Normal, Normal, Normal,
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f), filepath);

		//"./ObjectFile/FloorFile/dog.png");
		

}

void CFloor::Update_TranslateForm(GLfloat dx, GLfloat dy, GLfloat dz)
{
	m_Translate_Mat = glm::mat4(1.0f);
	m_Translate_Mat = glm::translate(m_Translate_Mat, glm::vec3(dx, dy, dz));


}

void CFloor::Update_RotateForm(GLfloat Time, GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat = glm::mat4(1.0f);
	m_Rotate_Mat = glm::rotate(m_Rotate_Mat, glm::radians(Time), glm::vec3(Axis_x, Axis_y, Axis_z));


}

void CFloor::Update_ScaleForm(GLfloat sx, GLfloat sy, GLfloat sz)
{
	m_Scale_Mat = glm::mat4(1.0f);
	m_Scale_Mat = glm::scale(m_Scale_Mat, glm::vec3(sx, sy, sz));


}
void CFloor::Update_ModelTransform()
{

	//Update_TranslateForm(0.0f, 0.0f, 0.0f);
	Update_RotateForm(0.0f);
	Update_ScaleForm();

	m_ModelMatrix_Result = glm::mat4(1.0f);
	m_ModelMatrix_Result = m_Translate_Mat * m_Rotate_Mat * m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));

	//GLint objColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	//glUniform3f(objColorLocation, 1.0f, 0.0f, 0.25f);

}

void CFloor::InitPosition()
{
	m_Position[0] = glm::vec3(-m_Floor_Size, 0.0f, m_Floor_Size);
	m_Position[1] = glm::vec3(m_Floor_Size, 0.0f, m_Floor_Size);
	m_Position[2] = glm::vec3(m_Floor_Size, 0.0f, -m_Floor_Size);
	m_Position[3] = glm::vec3(-m_Floor_Size, 0.0f, -m_Floor_Size);


}

void CFloor::InitColor()
{


	m_Colors[0] = glm::vec3(-1.0f, 0.0f, 1.0f);
	m_Colors[1] = glm::vec3(1.0f, 0.0f, 1.0f);
	m_Colors[2] = glm::vec3(-1.0f, 0.0f, -1.0f);
	m_Colors[3] = glm::vec3(-1.0f, 0.0f, -1.0f);
}

void CFloor::Render()
{
	Update_ModelTransform();

	if (m_Tri[0] != nullptr && m_Tri[1] != nullptr)
	{
		m_Tri[0]->Render();
		m_Tri[1]->Render();
	}
	
}

