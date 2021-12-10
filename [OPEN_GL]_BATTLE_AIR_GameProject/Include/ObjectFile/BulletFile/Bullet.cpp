#include "Bullet.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../../HeaderFile/stb_image.h"
#include "../HexaheronFile/hexahedron.h"



std::vector< glm::vec3 > CBullet::m_outvertex;
std::vector< glm::vec3 > CBullet::m_outnormal;
std::vector< glm::vec2 > CBullet::m_outuv;
GLint* CBullet::m_Tri_Num2;
GLint CBullet::m_Tri_Num = 1;


CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}


void CBullet::Update_TranslateForm(glm::vec3 translate)
{
	m_Translate_Mat = glm::mat4(1.0f);
	m_Translate_Mat = glm::translate(m_Translate_Mat, glm::vec3(translate));
}

void CBullet::Update_RotateForm(GLfloat Angle, GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat = glm::mat4(1.0f);
	m_Rotate_Mat = glm::rotate(m_Rotate_Mat, glm::radians(Angle), glm::vec3(Axis_x, Axis_y, Axis_z));
}

void CBullet::Update_ScaleForm(GLfloat sx, GLfloat sy, GLfloat sz)
{
	m_Scale_Mat = glm::mat4(1.0f);
	m_Scale_Mat = glm::scale(m_Scale_Mat, glm::vec3(sx, sy, sz));
}

void CBullet::Update_Rotate_LR(GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat_LR = glm::mat4(1.0f);
	m_Rotate_Mat_LR = glm::rotate(m_Rotate_Mat_LR, glm::radians((m_Angle + 180.0f) * -1), glm::vec3(Axis_x, Axis_y, Axis_z));


}


void CBullet::Update_ModelTransform(float fDeltaTime)
{

	/*glm::mat4 Rotate_Mat_Origin = glm::mat4(1.0f);
	Rotate_Mat_Origin = glm::rotate(Rotate_Mat_Origin, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

	m_ModelMatrix_Result = glm::mat4(1.0f);
	m_ModelMatrix_Result = m_Translate_Mat *m_Rotate_Mat_LR *m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));
}

void CBullet::Init(glm::vec3 scaleInfo, glm::vec3 color, glm::vec3 pivot, const char* filename, GLfloat angle , stbi_uc* textData2,int text_width, int text_height)
{

	// *** 충돌 박스 초기화 ***
	/*m_CollideBox = new Chexahedron;
	m_CollideBox->Init(1.0f, 2.5f, 1.0f, pivot, textData2, text_width, text_height);*/

	m_Angle = angle;
	m_Pivot = pivot;
	m_Color = color;


	Update_ScaleForm(scaleInfo.x, scaleInfo.y, scaleInfo.z);
	Update_Rotate_LR(0.0f, 1.0f, 0.0f);

	//cout << "CBullet Iniit :"<< m_Pivot.x << " " << m_Pivot.y << " " << m_Pivot.z << endl;

 	Update_TranslateForm(m_Pivot);

	if (m_Tri_Num == 1)
		m_Tri_Num = loadObj_normalize_center(filename);

	

	InitTexture_1(textData2, text_width , text_height);
	InitBuffer();

	

	m_Angle = angle;
	m_Pivot = pivot;
	m_Color = color;

	
}

void CBullet::Input(float fDeltaTime)
{
}

int CBullet::Update(float fDeltaTime)
{
	m_dist += fDeltaTime * m_Speed;

	m_Pivot.x += fDeltaTime * m_Speed * cos(glm::radians((m_Angle)));
	m_Pivot.z += fDeltaTime * m_Speed * sin(glm::radians((m_Angle)));
	Update_TranslateForm(m_Pivot);


	if (m_dist >= m_Limit_dist)
		m_bEnable = false;

	/*if (m_CollideBox != nullptr)
		m_CollideBox->Update_TranslateForm(m_Pivot);*/


	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CBullet::Collision(float fDeltaTime)
{
}

void CBullet::Render(float fDeltaTime)
{
	glBindVertexArray(m_VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Update_ModelTransform(fDeltaTime);

	m_Color = glm::vec3(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f);
	GLint objColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "objectColor"); 
	glUniform3f(objColorLocation, m_Color.x, m_Color.y, m_Color.z);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, m_Tri_Num);

	// *** 충돌 박스 출력 ***
	if (m_CollideBox != nullptr)
		m_CollideBox->Render();
}



void CBullet::InitTexture_1(stbi_uc* textData2, int width, int height)
{
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//unsigned char* data = LoadDIBitmap("dog.bmp", &bmp);
	stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가

	//stbi_uc* data = NULL;
	//const char* filename = "./ObjectFile/BulletFile/MissileTexture.png";

	//data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	////cout << data << endl;

	//cout << widthImage << " " << heightImage << endl;

	//if (!data) {
	//	fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
	//	exit(0);
	//}
	//cout << data << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData2);
	glGenerateMipmap(GL_TEXTURE_2D);

	unsigned int tLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "outTexture");
	glUniform1i(tLocation, 0);

	int i = 0;
	//stbi_image_free(textData2);

}


glm::vec3 CBullet::GetCollide_Position(int idx)
{
	
		if (m_CollideBox != nullptr)
		{
			return m_CollideBox->GetCollide_Position(idx);
		}

		return glm::vec3(0.0f, 0.0f, 0.0f);

}

int CBullet::loadObj_normalize_center(const char* filename)
{
	FILE* objFile = NULL;
	static int i = 0;
	cout << i++ << endl;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[512];
		// read the first word of the line
		int res = fscanf_s(objFile, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	std::cout << "scaleX: " << scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		temp = temp_vertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		m_outvertex.push_back(temp);
		//glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		//outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		m_outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		m_outnormal.push_back(vertex);
	}

	return m_outvertex.size();
}


void CBullet::InitBuffer()
{
	// V A O
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// V B O
	glGenBuffers(3, m_VBO);

	// < P O S I T O N >
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, m_outvertex.size() * sizeof(glm::vec3), &m_outvertex[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// < N O R M A L > 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, m_outnormal.size() * sizeof(glm::vec3), &m_outnormal[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	// < T E X T U R E > 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, m_outuv.size() * sizeof(glm::vec2), &m_outuv[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);

}
