#include "Axis.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"


CAxis::CAxis()
{
}

CAxis::~CAxis()
{
}

void CAxis::Update_TranslateForm(GLfloat dx, GLfloat dy, GLfloat dz)
{
	m_Translate_Mat = glm::mat4(1.0f);
	m_Translate_Mat = glm::translate(m_Translate_Mat, glm::vec3(dx, dy, dz));


}

void CAxis::Update_RotateForm(GLfloat Time, GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat = glm::mat4(1.0f);
	m_Rotate_Mat = glm::rotate(m_Rotate_Mat, glm::radians(Time), glm::vec3(Axis_x, Axis_y, Axis_z));



}

void CAxis::Update_ScaleForm(GLfloat sx, GLfloat sy, GLfloat sz)
{
	m_Scale_Mat = glm::mat4(1.0f);
	m_Scale_Mat = glm::scale(m_Scale_Mat, glm::vec3(sx, sy, sz));


}

void CAxis::Update_ModelTransform(float fDeltaTime)
{

	Update_TranslateForm(0.0f, 0.0f, 0.0f);
	Update_RotateForm(0.0f);
	Update_ScaleForm();


	m_ModelMatrix_Result = glm::mat4(1.0f);
	m_ModelMatrix_Result = m_Translate_Mat * m_Rotate_Mat * m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));


}

void CAxis::InitBuffer()
{
	// V A O
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// V B O
	glGenBuffers(2, m_VBO);

	// < P O S I T O N >
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Position), m_Position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// < N O R M A L > 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Normal), m_Normal, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

}

void CAxis::Init(GLfloat pivot)
{
	// X
	m_Position[0] = { pivot - m_Size, pivot , pivot };
	m_Position[1] = { pivot + m_Size, pivot , pivot };
	// Y
	m_Position[2] = { pivot , pivot - m_Size, pivot };
	m_Position[3] = { pivot , pivot + m_Size, pivot };
	// Z
	m_Position[4] = { pivot , pivot , pivot - m_Size };
	m_Position[5] = { pivot , pivot , pivot + m_Size };

	// X
	m_Normal[0] = { 0.0f, 1.0f, 0.0f };
	// Y
	m_Normal[1] = { 0.0f, 0.0f, 1.0f };
	// Z
	m_Normal[2] = { 0.0f, 1.0f, 0.0f };

	
	InitBuffer();

}

void CAxis::Input(float fDeltaTime)
{
}

int CAxis::Update(float fDeltaTime)
{
	return 0;
}

int CAxis::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CAxis::Collision(float fDeltaTime)
{
}

void CAxis::Render(float fDeltaTime)
{
	Update_ModelTransform(fDeltaTime);

	glUseProgram(CShaderProgramManger::Get_ShaderProgramID());
	glBindVertexArray(m_VAO);
	GLint objColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, 0.5f, 0.5f, 0.5f);


	glLineWidth(2.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 2);	//X	
	glDrawArrays(GL_LINE_LOOP, 2, 2);	//Y
	glDrawArrays(GL_LINE_LOOP, 4, 2);	//Z


}
