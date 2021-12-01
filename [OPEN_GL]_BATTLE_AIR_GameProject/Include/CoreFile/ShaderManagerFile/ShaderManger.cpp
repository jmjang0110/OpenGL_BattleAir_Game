
#include "../ShaderManagerFile/ShaderManger.h"
#include "../FileManagerFile/FileManager.h"

GLuint CShaderProgramManger::ShaderProgramID = NULL;
GLuint CShaderProgramManger::ShaderProgramID_Texture = NULL;
DEFINITION_SINGLE(CShaderProgramManger);


CShaderProgramManger::CShaderProgramManger()
{
	m_fragmentShader = -1;
	m_vertexShader = -1;
	ShaderProgramID = -1;

	m_fragmentShader_texture = -1;
	m_vertexShader_texture = -1;
	ShaderProgramID_Texture = -1;


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

	if (!InitShader_Texture())
	{
		cout << "Shader Program [ Texture ] Init Fail! " << endl;
		return false;

	}

	return true;

}


bool CShaderProgramManger::Make_VertexShaders()
{
	GLchar* vertexsource;
	vertexsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/VertexShader.glsl");

	// vertex Shader 객체 생성
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, (const GLchar**)&vertexsource, NULL);
	glCompileShader(m_vertexShader);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(m_vertexShader, 512, NULL, errorLog);
		cerr << "ERROR : Vertex Shader Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;

}

bool CShaderProgramManger::Make_FragmentShaders()
{
	GLchar* fragmentsource;
	fragmentsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/FragmentShader.glsl");

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &fragmentsource, NULL);
	glCompileShader(m_fragmentShader);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR : Fragment Shader Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;
}

bool CShaderProgramManger::InitShader()
{
	bool mVS = Make_VertexShaders();
	bool mFS = Make_FragmentShaders();

	if (mVS == false || mFS == false)
		return false;

	ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, m_vertexShader);
	glAttachShader(ShaderProgramID, m_fragmentShader);
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
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);

	// Use Shader Program
	glUseProgram(ShaderProgramID);

	return true;


}



// ==============================================
// Texture Shader Program Init
// ==============================================


bool CShaderProgramManger::Make_FragmentShaders_Texrure()
{

	GLchar* fragmentsource;
	fragmentsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/FragmentTexture.glsl");

	m_fragmentShader_texture = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader_texture, 1, &fragmentsource, NULL);
	glCompileShader(m_fragmentShader_texture);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(m_fragmentShader_texture, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(m_fragmentShader_texture, 512, NULL, errorLog);
		cerr << "ERROR : Fragment Shader Texture Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;
}

bool CShaderProgramManger::Make_VertexShaders_Texture()
{
	GLchar* vertexsource;
	vertexsource = m_fileManager->filetobuf("./CoreFile/ShaderManagerFile/VertexTexture.glsl");

	// vertex Shader 객체 생성
	m_vertexShader_texture = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader_texture, 1, (const GLchar**)&vertexsource, NULL);
	glCompileShader(m_vertexShader_texture);

	// Compile Error Check
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(m_vertexShader_texture, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(m_vertexShader_texture, 512, NULL, errorLog);
		cerr << "ERROR : Vertex Shader Texture Compile Fail!\n\a" << errorLog << endl;

		return false;
	}

	return true;
}

bool CShaderProgramManger::InitShader_Texture()
{
	bool mVS = Make_VertexShaders_Texture();
	bool mFS = Make_FragmentShaders_Texrure();

	if (mVS == false || mFS == false)
		return false;

	ShaderProgramID_Texture = glCreateProgram();

	glAttachShader(ShaderProgramID_Texture, m_vertexShader_texture);
	glAttachShader(ShaderProgramID_Texture, m_fragmentShader_texture);
	glLinkProgram(ShaderProgramID_Texture);

	GLint result;
	glGetProgramiv(ShaderProgramID_Texture, GL_LINK_STATUS, &result);
	GLchar errorLog[512]{ NULL };

	if (!result)
	{
		glGetShaderInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR : Shader Program Compile Fail!! \n\a" << errorLog << endl;
		return false;
	}

	// Shader Delete 
	// 이미 링크 했으므로 삭제해도 무방하다.
	glDeleteShader(m_vertexShader_texture);
	glDeleteShader(m_fragmentShader_texture);

	// Use Shader Program
	glUseProgram(ShaderProgramID_Texture);



	return true;

}


