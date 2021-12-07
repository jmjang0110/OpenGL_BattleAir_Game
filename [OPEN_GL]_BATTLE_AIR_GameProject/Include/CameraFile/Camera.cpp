#include "Camera.h"
#include "../ObjectFile/AirplaneFile/Airplane.h"
#include "../CoreFile/ShaderManagerFile/ShaderManger.h"
#include "../LightFile/Light.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

// xpos,ypos,zpos를통해서 피봇점을 기준으로 카메라위치를 변경해 줄건데
// 왼쪽으로 어느정도 이동하면 카메라 위치를 왼쪽으로 옮기고
// 오른쪽으로 어느정도 이동하면 카메라 위치를 오른쪽으로 옮기는데 사용 할거임
void CCamera::UPdate_Pivot_From_Airplane(glm::vec3 air_pivot,float xpos,float ypos,float zpos)
{
	cout << "px = " << air_pivot.x << "py = " << air_pivot.y << "pz = " << air_pivot.z << endl<<endl;
	m_cameraPos.x = air_pivot.x+xpos;
	m_cameraPos.y = air_pivot.y+ypos;
	m_cameraPos.z = air_pivot.z+zpos;

}

void CCamera::UPdate_Dir_From_Airplane(glm::vec3 air_dir)
{
	cout << "dx = " << air_dir.x << "dy = " << air_dir.y << "dz = " << air_dir.z << endl << endl;

	m_cameraDirection = air_dir;
}

void CCamera::UPdate_Camera_Mat_From_Airplane(glm::mat4 trans, glm::mat4 rotate, glm::mat4 scale)
{
	m_Translate_Mat = trans;
	m_Rotate_Mat = rotate;
	m_Scale_Mat = scale;
}

void CCamera::UpdateCameraMat(float fDeltaTime)
{
	m_View = glm::mat4(1.0f);
	m_View = glm::lookAt(m_cameraPos, m_cameraDirection, m_cameraUp);

	m_View_Mat_Result = m_View; //*m_Translate_Mat* m_Rotate_Mat* m_Scale_Mat;

	unsigned int viewLocation = glGetUniformLocation(CShaderProgramManger::Get_ShaderProgramID(), "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_View_Mat_Result));

}

bool CCamera::Init(glm::vec3 CameraPos, glm::vec3 CameraDir, glm::vec3 CameraUp)
{
	m_cameraPos = CameraPos;
	m_cameraDirection = CameraDir;
	m_cameraUp = CameraUp;


	return true;
}

void CCamera::Input(float fDeltaTime)
{
	// x값 + 
	if (GetAsyncKeyState('I') & 0x8000)
	{
		//cout << "camer input in" << endl;

		m_cameraPos.x += fDeltaTime * 5.0f;
	}
	// x값 -
	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_cameraPos.x -= fDeltaTime * 5.0f;
	}
	// y값 + 
	if (GetAsyncKeyState('J') & 0x8000)
	{
		m_cameraPos.y += fDeltaTime * 5.0f;
	}
	// y값 - 
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_cameraPos.y -= fDeltaTime * 5.0f;
	}
	// Z값 + 
	if (GetAsyncKeyState('O') & 0x8000)
	{
		m_cameraPos.z += fDeltaTime * 5.0f;
	}
	// Z값 - 
	if (GetAsyncKeyState('P') & 0x8000)
	{
		m_cameraPos.z -= fDeltaTime * 5.0f;
	}
	//cout << "camer input in" << endl;
}


int CCamera::Update(float fDeltaTime)
{

	UpdateCameraMat(fDeltaTime);

	return 0;
}

int CCamera::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CCamera::Collision(float fDeltaTime)
{
}

void CCamera::Render(float fDeltaTime)
{

	UpdateCameraMat(fDeltaTime);



}
