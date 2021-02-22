#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class ShaderProgram
{
	GLint program;
	void CompileShader(GLuint, const GLchar*);
	void Link();
public:
	ShaderProgram(const char*, const char*);
	GLint GetIndex() const;
	void Use() const;
};

