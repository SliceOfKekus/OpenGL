#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers.h"
#include "ShaderProgram.h"

extern GLfloat angleInRadians;
extern GLfloat mixValue;

using std::vector;

class GameWindow
{
	GLFWwindow* window;
	ShaderProgram program;
	mutable vector<GLuint> texture;
	vector<GLuint> VAO;
	vector<GLuint> VBO;
	vector<GLuint> IBO;
public:
	GameWindow(int, int, const char*, const char*);
	void CreateBuffers(const GLfloat*, GLsizeiptr, 
										 const GLuint*, GLsizeiptr);
	void LoadTexture(const char*) const noexcept;
	void Render();
	void SetCallback(void(*)(GLFWwindow*, int, int, int, int));

	~GameWindow();
};