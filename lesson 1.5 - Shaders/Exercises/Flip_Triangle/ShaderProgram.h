#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class ShaderProgram
{
	GLint program;
public:
	ShaderProgram(const char*, const char*);
	void 	Use();
};

