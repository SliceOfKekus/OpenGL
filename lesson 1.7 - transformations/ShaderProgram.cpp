#include "ShaderProgram.h"

void ShaderProgram::ReadyToUseProgram(const GLchar* vSource, 
																			const GLchar* fSource) const noexcept
{	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint success;
	GLchar log[512];

	glShaderSource(vShader, 1, &vSource, nullptr);
	glCompileShader(GL_VERTEX_SHADER);
	glGetProgramiv(vShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(vShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
		std::cout << log << "\n";
	}

	glShaderSource(fShader, 1, &fSource, nullptr);
	glCompileShader(GL_FRAGMENT_SHADER);
	glGetProgramiv(fShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(fShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
		std::cout << log << "\n";
	}
	
	if (program == 0)
		this->program = glCreateProgram();

	glAttachShader(this->program, vShader);
	glAttachShader(this->program, fShader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->program, sizeof(log), nullptr, log);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n";
		std::cout << log << "\n";
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void ShaderProgram::Load(const char* vPath, const char* fPath)
{

	std::string vCode;
	std::string fCode;
	std::ifstream vFile;
	std::ifstream fFile;

	vFile.exceptions(std::ifstream::failbit);
	fFile.exceptions(std::ifstream::failbit);

	try
	{
		std::stringstream vSource;
		std::stringstream fSource;

		vFile.open(vPath);
		fFile.open(fPath);

		vSource << vFile.rdbuf();
		fSource << fFile.rdbuf();

		vCode = vSource.str();
		fCode = fSource.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "FILE_NOT_SUCCESSFULLY_READ\n";
		std::cout << e.what() << std::endl;
	}

	const GLchar* vShader = vCode.c_str();
	const GLchar* fShader = fCode.c_str();

	ReadyToUseProgram(vShader, fShader);
}

ShaderProgram::ShaderProgram()
	: program(0)
{}

void ShaderProgram::Use() const noexcept
{
	glUseProgram(this->program);
}

GLint ShaderProgram::GetIndex() const
{
	return program;
}
