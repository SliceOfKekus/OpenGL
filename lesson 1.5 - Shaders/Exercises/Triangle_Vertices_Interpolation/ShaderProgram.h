#pragma once
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>

#include <glew.h>
class ShaderProgram
{
	mutable GLint program;
	void ReadyToUseProgram(const GLchar*, const GLchar*) const noexcept;
public:
	ShaderProgram(const char*, const char*);
	void Use() const noexcept;
};

