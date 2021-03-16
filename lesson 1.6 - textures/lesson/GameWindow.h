#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>
#include <vector>

#include "ShaderProgram.h"

class GameWindow
{
	GLFWwindow* window;
	ShaderProgram program;
	mutable std::vector<GLuint> texture;
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
public:
	GameWindow(int, int, const char*, const char*);
	void CreateBuffers(const GLfloat*, GLsizeiptr, 
										 const GLuint*, GLsizeiptr);
	void LoadTexture(const char*) const noexcept;
	void Render();

	~GameWindow();
};

