#include "Shader.h"


using namespace Engine;

Shader::Shader(string vertexPath, string fragmentPath)
{
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
	Build();
}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(this->programId);
}

GLuint Engine::Shader::GetId()
{
	return this->programId;
}

void Engine::Shader::setInt(int i, string str)
{
	glUniform1i(glGetUniformLocation(programId, str.c_str()), i);
}

void Engine::Shader::setFloat(float i, string str)
{
	glUniform1f(glGetUniformLocation(programId, str.c_str()), i);
}

void Engine::Shader::setMat4(mat4 mat, string str)
{
	glUniformMatrix4fv(glGetUniformLocation(programId, str.c_str()), 1, GL_FALSE, value_ptr(mat));
}

void Engine::Shader::setVec3(vec3 data, string str)
{
	glUniform3f(glGetUniformLocation(programId, str.c_str()), data.x, data.y, data.z);
}

void Shader::Validate(GLuint shaderId, string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
			throw "Failed to compile shader program.";
		}
	}
	else
	{
		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderId, 1024, NULL, infoLog);
			throw "Failed to link shader program.";
		}
	}
}

void Shader::Build()
{
	// 1. Retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		// Open files
		vShaderFile.open(this->vertexPath);
		fShaderFile.open(this->fragmentPath);
		stringstream vShaderStream, fShaderStream;

		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		throw "Failed to open shader files.";
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	// 2. Compile shaders
	GLuint vertex, fragment;

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	Validate(vertex, "VERTEX");

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	Validate(fragment, "FRAGMENT");

	// Shader Program
	this->programId = glCreateProgram();
	glAttachShader(this->programId, vertex);
	glAttachShader(this->programId, fragment);
	glLinkProgram(this->programId);
	Validate(this->programId, "PROGRAM");

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}
