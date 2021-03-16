#pragma once
//#define GLEW_STATIC
#include <glew.h>

#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

using std::shared_ptr;

class ShaderProgram
{
	mutable GLint program;
	void ReadyToUseProgram(const GLchar*, const GLchar*) const noexcept;
public:
	void Load(const char*, const char*);	
	ShaderProgram();
	void Use() const noexcept;
	GLint GetIndex() const;
};