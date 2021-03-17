#pragma once
#include "Headers.h"
#include "ShaderProgram.h"

extern GLfloat mixValue;

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
	void SetCallback(void(*)(GLFWwindow*, int, int, int, int));

	~GameWindow();
};