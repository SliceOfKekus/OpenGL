#include "ShaderProgram.h"

void ShaderProgram::CompileShader(GLuint index, const GLchar* source)
{
	GLchar log[512];
	GLint success;

	glShaderSource(index, 1, &source, nullptr);
	glCompileShader(index);
	glGetProgramiv(index, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(index, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n";
		std::cout << log << "\n";
		return;
	}

	glAttachShader(this->program, index);
}

void ShaderProgram::Link()
{
	GLchar log[512];
	GLint success;

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->program, sizeof(log), nullptr, log);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n";
		std::cout << log << "\n";
	}
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit);
	fragmentFile.exceptions(std::ifstream::failbit);

	try
	{
		std::stringstream vShader;
		std::stringstream fShader;

		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		vShader << vertexFile.rdbuf();
		fShader << fragmentFile.rdbuf();
		
		vertexCode = vShader.str();
		fragmentCode = fShader.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
		std::cout << e.what() << "\n";
	}

	const GLchar* vShader = vertexCode.c_str();
	const GLchar* fShader = fragmentCode.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	this->program = glCreateProgram();
	CompileShader(vertexShader, vShader);
	CompileShader(fragmentShader, fShader);
	Link();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint ShaderProgram::GetIndex() const
{
	return this->program;
}

void ShaderProgram::Use() const
{
	glUseProgram(this->program);
}
