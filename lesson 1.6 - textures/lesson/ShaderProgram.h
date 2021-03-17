#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Headers.h"

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