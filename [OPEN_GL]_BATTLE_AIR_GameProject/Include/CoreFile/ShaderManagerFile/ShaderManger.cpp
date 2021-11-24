
#include "../ShaderManagerFile/ShaderManger.h"
#include "../FileManagerFile/FileManager.h"

GLuint CShaderProgramManger::ShaderProgramID = NULL;
DEFINITION_SINGLE(CShaderProgramManger);


CShaderProgramManger::CShaderProgramManger()
{
	fragmentShader = -1;
	vertexShader = -1;
	ShaderProgramID = -1;


}
CShaderProgramManger::~CShaderProgramManger()
{
	if (m_fileManager != nullptr)
		delete m_fileManager;


}
bool CShaderProgramManger::Init()
{
	if (m_fileManager == nullptr)
		m_fileManager = new CFileManager;



	if (!InitShader())
	{
		cout << "Shader Program Init Fail! " << endl;
		return false;
	}

	return true;

}


bool CShaderProgramManger::Make_VertexShaders()
{
	GLchar* vertexsource;
	vertexsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/VertexShader.glsl");

	// vertex Shader 객체 생성
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexsource, NULL);
	glCompileShader(vertexShader);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR : Vertex Shader Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;

}

bool CShaderProgramManger::make_FragmentShaders()
{
	GLchar* fragmentsource;
	fragmentsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/FragmentShader.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
	glCompileShader(fragmentShader);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR : Fragment Shader Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;
}

bool CShaderProgramManger::InitShader()
{
	bool mVS = Make_VertexShaders();
	bool mFS = make_FragmentShaders();

	if (mVS == false || mFS == false)
		return false;

	ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexShader);
	glAttachShader(ShaderProgramID, fragmentShader);
	glLinkProgram(ShaderProgramID);

	GLint result;
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
	GLchar errorLog[512]{ NULL };

	if (!result)
	{
		glGetShaderInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR : Shader Program Compile Fail!! \n\a" << errorLog << endl;
		return false;
	}

	// Shader Delete 
	// 이미 링크 했으므로 삭제해도 무방하다.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Use Shader Program
	glUseProgram(ShaderProgramID);


}


