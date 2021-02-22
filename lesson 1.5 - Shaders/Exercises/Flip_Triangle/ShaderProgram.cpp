#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode, 
							fragmentCode;
	std::ifstream vShaderFile,
								fShaderFile;
	
	vShaderFile.exceptions(std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::failbit);

	try
	{
		std::stringstream vStream,
											fStream;

		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		vStream << vShaderFile.rdbuf();
		fStream << fShaderFile.rdbuf();
		
		vertexCode = vStream.str();
		fragmentCode = fStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
		std::cout << e.what() << "\n";
	}

	const GLchar* vShader = vertexCode.c_str();
	const GLchar* fShader = fragmentCode.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER),
				 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint success;
	GLchar log[512];

	glShaderSource(vertexShader, 1, &vShader, nullptr);
	glCompileShader(vertexShader);
	glGetProgramiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(vertexShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << "\n";
	}

	glShaderSource(fragmentShader, 1, &fShader, nullptr);
	glCompileShader(fragmentShader);
	glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(fragmentShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
		std::cout << log << "\n";
	}



	this->program = glCreateProgram();
	glAttachShader(this->program, vertexShader);
	glAttachShader(this->program, fragmentShader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Use()
{
	glUseProgram(this->program);
}
