#include "Scene.h"
#include "SceneManager.h"
#include "../LightFile/Light.h"
#include "../CameraFile/Camera.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../ObjectFile/AxisFile/Axis.h"

#include "../ObjectFile/AirplaneFile/Airplane.h"
#include "../ObjectFile/MonsterFile/Monster1.h"
#include "../ObjectFile/MonsterFile/Monster2.h"
#include "../ObjectFile/MonsterFile/Monster3.h"
#include "../ObjectFile/MonsterFile/Ballon.h"


#include "../ObjectFile/BackgroundFile/Background.h"
#include "../ObjectFile/BuildingFile/Building1.h"
#include "../ObjectFile/BuildingFile/Building2.h"
#include "../ObjectFile/BuildingFile/Building3.h"



#include "../ObjectFile/FloorFile/Floor.h"
#include "../ObjectFile/TriangleFile/Triangle.h"
#include "../SoundFile/SoundManager.h"

#include "../ObjectFile/BulletFile/BulletList.h"
#include "../ObjectFile/BulletFile/Bullet.h"

#include "../ObjectFile/HexaheronFile/hexahedron.h"
#include "../ObjectFile/BuildingFile/MapManager.h"
#include "../ObjectFile/MonsterFile/MonsterManager.h"




CScene::CScene()
{
	m_bEnable = false;


}

CScene::~CScene()
{
	if (m_Camera != nullptr)
		delete m_Camera;

	if (m_Light != nullptr)
		delete m_Light;

	if (m_Airplane != nullptr)
		delete m_Airplane;

	if (m_Monster1 != nullptr)
		delete m_Monster1;

	if (m_Monster2 != nullptr)
		delete m_Monster2;

	if (m_Monster3 != nullptr)
		delete m_Monster3;

	if (m_AirBallon != nullptr)
		delete m_Monster3;

	if (m_Background != nullptr)
		delete m_Background;

	if (m_Building1 != nullptr)
		delete m_Building1;

	if (m_Building2 != nullptr)
		delete m_Building2;

	if (m_Building3 != nullptr)
		delete m_Building3;

	if (m_triangle != nullptr)
		delete m_triangle;

	if (m_Floor != nullptr)
		delete[] m_Floor;


	stbi_image_free(m_Airplane_Text_data);
	stbi_image_free(m_Bullet_Text_data);

	stbi_image_free(m_Monster1_Text_data);
	stbi_image_free(m_Monster2_Text_data);
	stbi_image_free(m_Monster3_Text_data);
	stbi_image_free(m_airballon_Text_data);

	stbi_image_free(m_Building1_Text_data);
	stbi_image_free(m_Building2_Text_data);
	stbi_image_free(m_Building3_Text_data);

}

void CScene::InitTexture_All()
{

	// *** 비행기 텍스처 데이터 저장 ***
	stbi_set_flip_vertically_on_load(true);
	const char* filename = "./ObjectFile/AirplaneFile/jet.jpg";
	int widthImage = 0, heightImage = 0, numberOfChannel = 0;
	m_Airplane_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Airplane_width = widthImage;
	m_Airplane_height = heightImage;

	cout << widthImage << " " << heightImage << endl;

	if (!m_Airplane_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** 미사일( Bullet ) 텍스처 데이터 저장 ***
	filename = "./ObjectFile/BulletFile/MissileTexture.png";
	m_Bullet_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Bullet_width = widthImage;
	m_Bullet_height = heightImage;

	cout << widthImage << " " << heightImage << endl;

	if (!m_Bullet_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}


	// *** Red 텍스처 데이터 저장 ***
	filename = "./ObjectFile/HexaheronFile/Red.png";
	m_RedPng_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_RedPng_width = widthImage;
	m_RedPng_height = heightImage;

	cout << widthImage << " " << heightImage << endl;

	if (!m_RedPng_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Grass 텍스처 데이터 저장 ***
	filename = "./ObjectFile/FloorFile/grass.jpg";
	m_Grass_Text_dtat = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Grass_width = widthImage;
	m_Grass_height = heightImage;

	cout << m_Grass_width << " " << m_Grass_height << endl;

	if (!m_Grass_Text_dtat) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Airballon 텍스처 데이터 저장 ***
	filename = "./ObjectFile/MonsterFile/ballon.jpg";
	m_airballon_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_airballon_width = widthImage;
	m_airballon_height = heightImage;

	cout << m_airballon_width << " " << m_airballon_height << endl;

	if (!m_airballon_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Monster1 텍스처 데이터 저장 ***

	filename = "./ObjectFile/MonsterFile/bird.png";
	m_Monster1_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Monster1_width = widthImage;
	m_Monster1_height = heightImage;

	cout << m_Monster1_width << " " << m_Monster1_height << endl;

	if (!m_Monster1_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Monster2 텍스처 데이터 저장 ***
	filename = "./ObjectFile/MonsterFile/Gargoyle_1_Mask.jpg";
	m_Monster2_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Monster2_width = widthImage;
	m_Monster2_height = heightImage;

	cout << m_Monster2_width << " " << m_Monster2_height << endl;

	if (!m_Monster2_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Monster3 텍스처 데이터 저장 ***
	filename = "./ObjectFile/MonsterFile/monster2.jpg";
	m_Monster3_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Monster3_width = widthImage;
	m_Monster3_height = heightImage;

	cout << m_Monster3_width << " " << m_Monster3_height << endl;

	if (!m_Monster3_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}


	// *** Building1 텍스처 데이터 저장 ***
	filename = "./ObjectFile/BuildingFile/Brown.jpg";
	m_Building1_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Building1_width = widthImage;
	m_Building1_height = heightImage;

	cout << m_Building1_width << " " << m_Building1_height << endl;

	if (!m_Building1_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Building2 텍스처 데이터 저장 ***
	filename = "./ObjectFile/BuildingFile/WindMill.jpg";
	m_Building2_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Building2_width = widthImage;
	m_Building2_height = heightImage;

	cout << m_Building2_width << " " << m_Building2_height << endl;

	if (!m_Building2_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

	// *** Building3 텍스처 데이터 저장 ***
	filename = "./ObjectFile/BuildingFile/top.jpg";
	m_Building3_Text_data = stbi_load(filename, &widthImage, &heightImage, &numberOfChannel, STBI_rgb);
	m_Building3_width = widthImage;
	m_Building3_height = heightImage;

	cout << m_Building3_width << " " << m_Building3_height << endl;

	if (!m_Building3_Text_data) {
		fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", filename, stbi_failure_reason());
		exit(0);
	}

}

void CScene::UpdateProjectionMat()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_SIZE_WIDTH / (float)WINDOW_SIZE_HEIGHT, 0.1f, 1000.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

}

void CScene::UpdateOrthoMat()
{
	glm::mat4 Ortho = glm::mat4(1.0f);
	Ortho = glm::ortho(-1.5f, 1.5f, -1.5f, 1.5f, 0.1f, 50.0f);
	Ortho = glm::translate(Ortho, glm::vec3(0.0, 0.0, -1.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &Ortho[0][0]);

}

void CScene::Init_MainStage(SCENE_TYPE type)
{

	// 텍스처 정보들을 저장합니다. 
	InitTexture_All();


	
	if (CSoundManager::GetInst()->Init())
	{
		cout << "Sound File Load Success" << endl;

	}


	if (m_Airplane == nullptr)
	{
		m_Airplane = new CAirplane;
		// Init( scale color Pivot FileName )  
		m_Airplane->Init(glm::vec3(2.0f, 0.8f, 2.0f), glm::vec3(255.0f / 255.0f, 153.0f / 255.0f, rand() % 255 / 255.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), "./ObjectFile/AirplaneFile/jet.obj",
			m_Airplane_Text_data, m_Bullet_Text_data, m_RedPng_Text_data,
			m_Airplane_width, m_Airplane_height,
			m_Bullet_width, m_Bullet_height,
			m_RedPng_width, m_RedPng_height);
	}

	if (m_AirBallon == nullptr)
	{
		m_AirBallon = new CAirballon;
		m_AirBallon->Init(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-15.0f, 15.0f, 15.0f), "./ObjectFile/MonsterFile/ballon.obj", m_airballon_Text_data, m_RedPng_Text_data,
			m_airballon_width, m_airballon_height, m_RedPng_width, m_RedPng_height);

	}

	if (m_Monster1 == nullptr)
	{
		m_Monster1 = new CMonster1;
		m_Monster1->Init(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
			glm::vec3(0.0f, 0.0f, -0.0f), "./ObjectFile/MonsterFile/bird.obj", m_Monster1_Text_data, m_RedPng_Text_data,
			m_Monster1_width, m_Monster1_height, m_RedPng_width, m_RedPng_height);

	}

	if (m_Monster2 == nullptr)
	{
		m_Monster2 = new CMonster2;
		m_Monster2->Init(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
			glm::vec3(10.0f, 10.0f, -0.0f), "./ObjectFile/MonsterFile/Gargoyle_1.obj", m_Monster2_Text_data, m_RedPng_Text_data,
			m_Monster2_width, m_Monster2_height, m_RedPng_width, m_RedPng_height);

	}

	if (m_Monster3 == nullptr)
	{
		m_Monster3 = new CMonster3;
		m_Monster3->Init(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f),
			glm::vec3(-10.0f, 10.0f, -0.0f), "./ObjectFile/MonsterFile/monster2.obj", m_Monster3_Text_data, m_RedPng_Text_data,
			m_Monster3_width, m_Monster3_height, m_RedPng_width, m_RedPng_height);

	}

	// missile 초기화 
	/*if (m_Missile == nullptr)
	{
		m_Missile = new CBullet;
		m_Missile->Init(glm::vec3(2.0f / 3, 0.5f / 3, 0.5f / 3), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 1.0f, 5.0f),
			"./ObjectFile/BulletFile/Missile.obj", m_Airplane->GetAngleLR());

	}*/


	if (m_Camera == nullptr)
	{
		m_Camera = new CCamera;
		// 카메라 위치 , 바라보고있는 방향은 비행기 피봇값에의해 변동되므로 아래 파라미터 값들은 의미 없음
		m_Camera->Init(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.001f, 5.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	}
	if (m_Light == nullptr)
	{
		m_Light = new CLight;
		m_Light->Init(glm::vec3(-0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	}



	if (m_Axis == nullptr)
	{
		m_Axis = new CAxis;
		m_Axis->Init(0.0f);
	}

	if (m_Background == nullptr)
	{
		m_Background = new CBackground;
		m_Background->Init(glm::vec3(500.0f, 500.0f, 500.0f), glm::vec3(1.0, 1.0, 1.0),
			glm::vec3(0.0f, 0.0f, 0.0f), "./ObjectFile/BackgroundFile/sphere.obj");

	}

	if (m_Building1 == nullptr)
	{
		m_Building1 = new CBuilding1;
		m_Building1->Init(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(3.0f, 3.0f, 3.0f), "./ObjectFile/BuildingFile/BrownTown.obj", m_Building1_Text_data, m_RedPng_Text_data,
			m_Building1_width, m_Building1_height, m_RedPng_width, m_RedPng_height);

	}

	if (m_Building2 == nullptr)
	{
		m_Building2 = new CBuilding2;
		m_Building2->Init(glm::vec3(3.0f, 5.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-3.0f, -3.0f, -3.0f), "./ObjectFile/BuildingFile/WindMill.obj", m_Building2_Text_data, m_RedPng_Text_data,
			m_Building2_width, m_Building2_height, m_RedPng_width, m_RedPng_height);

	}

	if (m_Building3 == nullptr)
	{
		m_Building3 = new CBuilding3;
		m_Building3->Init(glm::vec3(15.0f, 30.0f, 15.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-20.0f, 3.0f, -3.0f), "./ObjectFile/BuildingFile/Floating Island.obj", m_Building3_Text_data, m_RedPng_Text_data,
			m_Building3_width, m_Building3_height, m_RedPng_width, m_RedPng_height);

	}


	//for (int i = 0; i < 4; ++i)
	//{
	//	if (m_Floor[i] == nullptr)
	//	{
	//		m_Floor[i] = new CFloor;
	//		m_Floor[i]->Init(m_Grass_Text_dtat, m_Grass_width, m_Grass_height);

	//	}

	//}

	CMapManager::GetInst()->Init(m_Building1_Text_data, m_Building2_Text_data, m_Building3_Text_data, m_RedPng_Text_data,
		m_Building1_width, m_Building1_height, m_Building2_width, m_Building2_height, m_Building3_width, m_Building3_height,
		m_RedPng_width, m_RedPng_height);

	CMonsterManager::GetInst()->Init(m_Monster1_Text_data, m_Monster2_Text_data, m_Monster3_Text_data, m_RedPng_Text_data,
		m_Monster1_width, m_Monster1_height, m_Monster2_width, m_Monster2_height, m_Monster3_width, m_Monster3_height,
		m_RedPng_width, m_RedPng_height);
}

void CScene::Init_BeginStage(SCENE_TYPE type)
{
}

void CScene::Init_EndStage(SCENE_TYPE type)
{
}

bool CScene::Init(SCENE_TYPE type)
{
	switch (type)
	{
	case NONE:
		break;
	case BEGIN:
		Init_BeginStage(type);
		break;
	case MAIN_STAGE:
		Init_MainStage(type);
		break;
	case END:
		Init_EndStage(type);

		break;
	default:
		break;
	}
	if (type == SCENE_TYPE::MAIN_STAGE)
	{

	}



	return true;
}

void CScene::Input(float fDeltaTime)
{

	if (m_Airplane != nullptr)
	{
		m_Airplane->Input(fDeltaTime);
	}

	//if (m_Camera != nullptr)
	//{
	//	m_Camera->Input(fDeltaTime);
	//}

}

int CScene::Update(float fDeltaTime)
{
	CSoundManager::GetInst()->Update();

	if (m_AirBallon != nullptr)
		m_AirBallon->Update(fDeltaTime);
	
	if (m_Monster1 != nullptr)
		m_Monster1->Update(fDeltaTime);
	
	if (m_Monster2 != nullptr)
		m_Monster2->Update(fDeltaTime);

	if (m_Monster3 != nullptr)
		m_Monster3->Update(fDeltaTime);

	if (m_Airplane != nullptr)
	{
		m_Airplane->Update(fDeltaTime);
		m_Airplane->Update_Rotate_LR(0.0f, 0.0f, 1.0f);

	}

	if (m_Missile != nullptr)
	{
		m_Missile->Update_Rotate_LR(0.0f, 1.0f, 0.0f);
		//m_Missile->Update(fDeltaTime);


	}

	if (m_Camera != nullptr)
	{
		m_Camera->UpdateCameraPos(m_Airplane->GetPivot(), m_Airplane->GetAngleLR());
		m_Camera->UpdateCameraDirection(m_Airplane->GetAngleLR());

		m_Camera->Update(fDeltaTime);

	}

	if (m_Light != nullptr)
	{
		m_Light->UpdateLightPos(m_Airplane->GetPivot(), m_Airplane->GetAngleLR(),m_Camera->GetCameraDir());

	}
	//CMapManager::GetInst()->Update(fDeltaTime);

	
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	/*if (m_Airplane != nullptr)
	{
		m_Airplane->LateUpdate(fDeltaTime);
	}*/
	return 0;
}


bool CScene::check_crash(Chexahedron* airplane, Chexahedron* obj)
{
	float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

	x1 = airplane->GetCollide_Position(3).x;
	y1 = airplane->GetCollide_Position(3).y;
	z1 = airplane->GetCollide_Position(3).z;

	x2 = airplane->GetCollide_Position(5).x;
	y2 = airplane->GetCollide_Position(5).y;
	z2 = airplane->GetCollide_Position(5).z;

	x3 = obj->GetCollide_Position(3).x;
	y3 = obj->GetCollide_Position(3).y;
	z3 = obj->GetCollide_Position(3).z;


	x4 = obj->GetCollide_Position(5).x;
	y4 = obj->GetCollide_Position(5).y;
	z4 = obj->GetCollide_Position(5).z;

	//cout << "--------------------------------------------------------------------" << endl;
	//cout << "비행기" << endl;
	//cout << " x1 = " << x1 << " y1 = " << y1 << " z1 = " << z1 << endl;
	//cout << " x2 = " << x2 << " y2 = " << y2 << " z2 = " << z2 << endl;

	//cout << "몬스터" << endl;
	//cout << " x3 = " << x3 << " y3 = " << y3 << " z3 = " << z3 << endl;
	//cout << " x4 = " << x4 << " y4 = " << y4 << " z4 = " << z4 << endl;
	//cout << "--------------------------------------------------------------------" << endl;


	if ((x1 <= x4 && x2 >= x3) && (y1 <= y4 && y2 >= y3) && (z1 <= z4 && z2 >= z3)) {
		return true;
	}

	return false;
}

bool CScene::check_crash_dot(glm::vec3 dot, class Chexahedron* obj)
{
	float x1, x2, y1, y2, z1, z2;

	x1 = obj->GetCollide_Position(3).x;
	y1 = obj->GetCollide_Position(3).y;
	z1 = obj->GetCollide_Position(3).z;

	x2 = obj->GetCollide_Position(5).x;
	y2 = obj->GetCollide_Position(5).y;
	z2 = obj->GetCollide_Position(5).z;

	if (((x1 <= dot.x) && (dot.x <= x2)) && ((y1 <= dot.y) && (dot.y <= y2)) && ((z1 <= dot.z) && (dot.z <= z2))) {
		return true;
	}

	return false;
}

void CScene::Collision(float fDeltaTime)
{
	if (m_Airplane != nullptr)
	{
		if (m_Monster1 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Monster1->m_CollideBox)) cout << "monster1 충돌" << endl;
		if (m_Monster2 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Monster2->m_CollideBox)) cout << "monster2 충돌" << endl;
		if (m_Monster3 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Monster3->m_CollideBox)) cout << "monster3 충돌" << endl;
		if (m_Building1 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Building1->m_CollideBox)) cout << "building1 충돌" << endl;
		if (m_Building2 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Building2->m_CollideBox)) cout << "building2 충돌" << endl;
		if (m_Building3 != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_Building3->m_CollideBox)) cout << "building3 충돌" << endl;
		if (m_AirBallon != nullptr) if (check_crash(m_Airplane->m_CollideBox, m_AirBallon->m_CollideBox)) cout << "air ballon 충돌" << endl;
	}

	if (m_Airplane != nullptr)
	{
		CBulletList* BulletList = m_Airplane->GetBulletList();
		BulletList->Collision(m_Monster1->m_CollideBox);
		BulletList->Collision(m_Monster2->m_CollideBox);
		BulletList->Collision(m_Monster3->m_CollideBox);

		



	}

}

void CScene::Render(float fDeltaTime)
{

	UpdateProjectionMat();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);



	if (m_Camera != nullptr)
		m_Camera->Render(fDeltaTime);

	if (m_Light != nullptr)
		m_Light->Render(fDeltaTime, m_Camera);

	if (m_Axis != nullptr)
		m_Axis->Render(fDeltaTime);

	if (m_Airplane != nullptr)
		m_Airplane->Render(fDeltaTime);


	if (m_Missile != nullptr)
	{
		m_Missile->Render(fDeltaTime);

	}

	if (m_AirBallon != nullptr)
		m_AirBallon->Render(fDeltaTime);

	if (m_Monster1 != nullptr)
		m_Monster1->Render(fDeltaTime);

	if (m_Monster2 != nullptr)
		m_Monster2->Render(fDeltaTime);

	if (m_Monster3 != nullptr)
		m_Monster3->Render(fDeltaTime);

	if (m_Background != nullptr)
		m_Background->Render(fDeltaTime);

	if (m_Building1 != nullptr)
		m_Building1->Render(fDeltaTime);

	if (m_Building2 != nullptr)
		m_Building2->Render(fDeltaTime);

	if (m_Building3 != nullptr)
		m_Building3->Render(fDeltaTime);

	//m_Floor[0]->Render();

	/*for (int i = 0; i < 4; ++i)
	{
		if (m_Floor[i] != nullptr)
		{
			m_Floor[i]->Render();

		}
	}*/

	CMapManager::GetInst()->Render(fDeltaTime);
	CMonsterManager::GetInst()->Render(fDeltaTime);


}


