#include "Triangle.h"
#include "../../HeaderFile/stb_image.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"


CTriangle::CTriangle()
{
}

CTriangle::~CTriangle()
{
}

void CTriangle::InitTexture_1(stbi_uc* textData3,
	int text_width, int text_height)
{
	unsigned int texture;
	BITMAPINFO* bmp;
	int widthImage = 0, heightImage = 0, numberOfChannel = 0;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가
	//stbi_uc* data = NULL;

	//const char* filename = filepath;// "./ObjectFile/FloorFile/grass.jpg";

	//data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	//cout << widthImage << " " << heightImage << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, 3, text_width, text_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData3);
	/*if (!textData3) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}*/

	unsigned int tLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "outTexture");
	glUniform1i(tLocation, 0);

	int i = 0;
	//stbi_image_free(data);

}

void CTriangle::InitBuffer()
{
	// V A O
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// V B O
	glGenBuffers(3, m_VBO);

	// < P O S I T O N >
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Position), m_Position, GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);


	// < I N D E X >
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Index), m_Index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);


	// < N O R M A L > 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Normal), m_Normal, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// < T E X T U R E > 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Texture), m_Texture, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

}

void CTriangle::Init(glm::vec3 Pos0, glm::vec3 Pos1, glm::vec3 Pos2, GLfloat R, GLfloat G, GLfloat B, glm::vec3 Normal1, glm::vec3 Normal2, glm::vec3 Normal3
	, glm::vec2 tex1, glm::vec2 tex2, glm::vec2 tex3, stbi_uc* textData3,
	int text_width, int text_height)
{
	InitPosition(Pos0, Pos1, Pos2);
	InitColor(R, G, B);
	InitNormal(Normal1, Normal2, Normal3);
	InitTexture(tex1, tex2, tex3);

	InitTexture_1(textData3, text_width, text_height);
	InitBuffer();



}

void CTriangle::InitTexture(glm::vec2 Pos0, glm::vec2 Pos1, glm::vec2 Pos2)
{
	m_Texture[0] = Pos0;
	m_Texture[1] = Pos1;
	m_Texture[2] = Pos2;

}
void CTriangle::InitPosition(glm::vec3 Pos0, glm::vec3 Pos1, glm::vec3 Pos2)
{
	m_Position[0] = Pos0;
	m_Position[1] = Pos1;
	m_Position[2] = Pos2;
}


void CTriangle::InitNormal(glm::vec3 Nor0, glm::vec3 Nor1, glm::vec3 Nor2)
{
	m_Normal[0] = Nor0;
	m_Normal[1] = Nor1;
	m_Normal[2] = Nor2;

}

void CTriangle::InitColor(GLfloat R, GLfloat G, GLfloat B)
{
	R = 1.0f;
	G = 1.0f;
	B = 1.0f;

	m_Colors[0] = glm::vec3(R, G, B);
	m_Colors[1] = glm::vec3(R, G, B);
	m_Colors[2] = glm::vec3(R, G, B);

}

void CTriangle::Update_TranslateForm(GLfloat dx, GLfloat dy, GLfloat dz)
{
	m_Translate_Mat = glm::mat4(1.0f);
	m_Translate_Mat = glm::translate(m_Translate_Mat, glm::vec3(dx, dy, dz));


}

void CTriangle::Update_RotateForm(GLfloat Time, GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat = glm::mat4(1.0f);
	m_Rotate_Mat = glm::rotate(m_Rotate_Mat, glm::radians(Time), glm::vec3(Axis_x, Axis_y, Axis_z));


}

void CTriangle::Update_ScaleForm(GLfloat sx, GLfloat sy, GLfloat sz)
{
	m_Scale_Mat = glm::mat4(1.0f);
	m_Scale_Mat = glm::scale(m_Scale_Mat, glm::vec3(sx, sy, sz));


}

void CTriangle::Update_ModelTransform()
{

	//Update_TranslateForm(0.0f, 0.0f, 0.0f);
	Update_RotateForm(0.0f);
	Update_ScaleForm();

	m_ModelMatrix_Result = glm::mat4(1.0f);
	m_ModelMatrix_Result = m_Translate_Mat * m_Rotate_Mat * m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));


}

void CTriangle::Render(RENDER_TYPE renderType )
{
	if (m_bEnable == GL_FALSE)
		return;

	glBindVertexArray(m_VAO);
	GLint objColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, m_Colors[0].x, m_Colors[0].y, m_Colors[0].z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	if(renderType == RENDER_TYPE::TRIANGLES)
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	else if(renderType == RENDER_TYPE::LINE)
		glDrawElements(GL_LINE, 3, GL_UNSIGNED_INT, 0);
	else if (renderType == RENDER_TYPE::LINE_LOOP)
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_POLYGON, 0, 3);


}
