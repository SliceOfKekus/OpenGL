#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers.h"
#include "ShaderProgram.h"

extern GLfloat angleInRadians;
extern GLfloat mixValue;
extern bool keys[1024];
extern GLfloat yawAngle;
extern GLfloat pitchAngle;
extern GLfloat fov;

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
	void SetKeyCallback(void(*)(GLFWwindow*, int, int, int, int));
	void SetMouseCallback(void(*)(GLFWwindow*, double, double));
	void SetScrollCallback(void(*)(GLFWwindow*, double, double));
	~GameWindow();
};