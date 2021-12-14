#include "Monster2.h"
#include "../../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../../HeaderFile/stb_image.h"
#include "../HexaheronFile/hexahedron.h"

#include "../TriangleFile/Triangle.h"


std::vector< glm::vec3 > CMonster2::m_outvertex;
std::vector< glm::vec3 > CMonster2::m_outnormal;
std::vector< glm::vec2 > CMonster2::m_outuv;
GLint* CMonster2::m_Tri_Num2;
GLint CMonster2::m_Tri_Num = 1;


std::random_device rd2;
std::default_random_engine dre2{ rd2() };
std::uniform_int_distribution<> uid_dir2(1, 4);

CMonster2::CMonster2()
{
}

CMonster2::~CMonster2()
{
}

void CMonster2::Update_Turn_Mat()
{
	m_Rotate_Turn_Mat = glm::mat4(1.0f);
	m_Rotate_Turn_Mat = glm::rotate(m_Rotate_Turn_Mat, glm::radians(m_Turn), glm::vec3(0.0f, 1.0f, 0.0f));
}

void CMonster2::Update_TranslateForm(glm::vec3 translate)
{
	m_Translate_Mat = glm::mat4(1.0f);
	m_Translate_Mat = glm::translate(m_Translate_Mat, glm::vec3(translate));
}

void CMonster2::Update_RotateForm(GLfloat Angle, GLfloat Axis_x, GLfloat Axis_y, GLfloat Axis_z)
{
	m_Rotate_Mat = glm::mat4(1.0f);
	m_Rotate_Mat = glm::rotate(m_Rotate_Mat, glm::radians(Angle), glm::vec3(Axis_x, Axis_y, Axis_z));
}

void CMonster2::Update_ScaleForm(GLfloat sx, GLfloat sy, GLfloat sz)
{
	m_Scale_Mat = glm::mat4(1.0f);
	m_Scale_Mat = glm::scale(m_Scale_Mat, glm::vec3(sx, sy, sz));
}

void CMonster2::Update_ModelTransform(float fDeltaTime)
{
	m_ModelMatrix_Result = m_Translate_Mat * m_Rotate_Turn_Mat * m_Rotate_Mat * m_Scale_Mat;

	unsigned int MLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "modelTransform");
	glUniformMatrix4fv(MLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix_Result));
}

void CMonster2::Init(glm::vec3 scaleInfo, glm::vec3 color, glm::vec3 pivot, const char* filename, stbi_uc* textData, stbi_uc* textData2,
	int text_monster_width, int text_monster_height,
	int textRed_height_width, int textRed_height_height,CTriangle** tri)
{

	m_tri = new CTriangle * [10];
	for (int i = 0; i < 10; ++i)
	{
		m_tri[i] = new CTriangle;
		//m_tri[i]->Init(0.5f, 0.5f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), textData2, text_width, text_height);
		m_tri[i] = tri[i];

	}


	m_Monster2_Text_data = textData;
	m_Pivot = pivot;
	m_Color = color;
	m_Pivot.y = m_Pivot.y + scaleInfo.y / 2;

	// *** 충돌 박스 초기화 ***
	m_CollideBox = new Chexahedron;
	m_CollideBox->Init(scaleInfo.x * 1.0f, scaleInfo.y * 1.0f, scaleInfo.z * 1.0f, m_Pivot, textData2, textRed_height_width, textRed_height_height);

	
	Update_ScaleForm(scaleInfo.x, scaleInfo.y, scaleInfo.z);
	Update_TranslateForm(m_Pivot);

	if (m_Tri_Num == 1)
		m_Tri_Num = loadObj_normalize_center(filename);

	m_Speed = 0.0f;

	InitTexture_1(m_Monster2_Text_data, text_monster_width, text_monster_height);
	InitBuffer();
	m_Pivot = pivot;
}

glm::vec3 CMonster2::GetCollide_Position(int idx)
{
	if (m_CollideBox != nullptr)
	{
		return m_CollideBox->GetCollide_Position(idx);
	}

	return glm::vec3(0.0f, 0.0f, 0.0f);

}

void CMonster2::Input(float fDeltaTime)
{
}

int CMonster2::Update(float fDeltaTime)
{
	if (m_bDie == true)
		return 0;



	//cout << "m_Dir= " << m_Dir << endl;
	if (m_bDie == false)
	{
		if (m_Dist > 5.0f) {
			// 1 = +x 2= -x 3= +z 4= -z 방향 (추가가능)
			m_Dir = uid_dir2(dre2);
			m_Dist = 0.0f;

		}
		//좌
		if (m_Dir == 1) {
			m_Pivot.x += (fDeltaTime * 2.0f);
			m_Dist += (fDeltaTime * 2.0f);

			m_Turn = 90.0f;

		}
		//우
		else if (m_Dir == 2) {
			m_Pivot.x -= (fDeltaTime * 1.0f);
			m_Dist += (fDeltaTime * 1.0f);
			m_Turn = 270.0f;

		}
		//하
		else if (m_Dir == 3) {
			m_Pivot.z += (fDeltaTime * 1.0f);
			m_Dist += (fDeltaTime * 1.0f);
			m_Turn = 0.0f;

		}
		//상
		else if (m_Dir == 4) {
			m_Pivot.z -= (fDeltaTime * 1.0f);
			m_Dist += (fDeltaTime * 1.0f);
			m_Turn = 180.0f;

		}

		Update_Turn_Mat();
		Update_TranslateForm(m_Pivot);


		if (m_CollideBox != nullptr)
			m_CollideBox->Update_TranslateForm(m_Pivot);
	}

	else if (m_bDie == true)
	{
		//m_Pivot.x += fDeltaTime * m_Speed / 3 * cos(glm::radians((m_Angle)));
		//m_Pivot.y += fDeltaTime * m_Speed / 3 * sin(glm::radians((m_Angle)));
		for (int i = 0; i < 10; ++i)
		{
			m_boomInfo[i].pivot.x += fDeltaTime * m_Speed / 10 * cos(glm::radians((m_boomInfo[i].angle)));
			m_boomInfo[i].pivot.y += fDeltaTime * m_Speed / 10 * sin(glm::radians((m_boomInfo[i].angle)));
			m_boomInfo[i].pivot.z += fDeltaTime * m_Speed / 10 * m_boomInfo[i].dir * sin(glm::radians((m_boomInfo[i].angle2)));

		}

		m_tri_Angle += 5.0f;

		if (m_tri_Angle >= 1000.0f)
			m_bEnable = false;

		//Update_TranslateForm(m_Pivot);
	}
	return 0;
}

int CMonster2::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CMonster2::Collision(float fDeltaTime)
{
}

void CMonster2::Render(float fDeltaTime)
{
	if (m_bDie == true)
		return ;

	glBindVertexArray(m_VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Update_ModelTransform(fDeltaTime);

	//m_Color = glm::vec3(255.0f / 255.0f, 102.0f / 255.0f,102.0f / 255.0f);
	GLint objColorLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, m_Color.x, m_Color.y, m_Color.z);

	if (m_bDie == false)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glDrawArrays(GL_TRIANGLES, 0, m_Tri_Num);

	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{

			m_tri[i]->Update_TranslateForm(m_boomInfo[i].pivot.x, m_boomInfo[i].pivot.y, m_boomInfo[i].pivot.z);
			m_tri[i]->Update_RotateForm(m_boomInfo[i].angle2, 1.0f, 1.0f, 1.0f);

			m_tri[i]->Update_ModelTransform();

			m_tri[i]->Render(RENDER_TYPE::TRIANGLES);

		}
	}


	// *** 충돌 박스 출력 ***
	//if (m_CollideBox != nullptr)
	//	m_CollideBox->Render();
}



void CMonster2::InitTexture_1(stbi_uc* textData, int text_moster_width, int text_moster_height)
{
	unsigned int texture;
	BITMAPINFO* bmp;
	int widthImage = 0, heightImage = 0, numberOfChannel = 0;
	m_Monster2_Text_data = textData;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가

	//cout << widthImage << " " << heightImage << endl;

	if (!m_Monster2_Text_data) {
		exit(0);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_moster_width, text_moster_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Monster2_Text_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	unsigned int tLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "outTexture");
	glUniform1i(tLocation, 0);

	int i = 0;
	//stbi_image_free(m_Monster2_Text_data);

}


int CMonster2::loadObj_normalize_center(const char* filename)
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


void CMonster2::InitBuffer()
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
