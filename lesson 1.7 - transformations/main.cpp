#include <iostream>
#include <cmath>

#include <stdio.h>

#include "Headers.h"
#include "GameWindow.h"

constexpr GLfloat PI = 3.14159265359;

GLfloat angleInRadians = PI;
GLfloat mixValue = 0.2f;

const int WIDTH = 1200;
const int HEIGHT = 1000;

const GLfloat vertices[] =
{
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
};

const GLuint indecies[] =
{
	0, 1, 3,
	1, 2, 3
};

const char* vSource = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\OpenGL\\lesson 1.7 - transformations\\lesson\\vertex.GLSL";
const char* fSource = "C:\\Users\\SliceOfKekus\\Desktop\\fragment.GLSL";
const char* container = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\container.jpg";
const char* awesomeFace = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\awesomeface.png";

void Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.f;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.f;
	}

	//if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	//{
	//	
	//	angleInRadians += PI / 6.f;
	//	if (angleInRadians >= 2 * PI)
	//		angleInRadians = std::fmod(angleInRadians, 2 * PI);
	//}
	//
	//if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	//{
	//	angleInRadians -= PI / 6.f;
	//	if (angleInRadians <= 0.f)
	//		angleInRadians = std::fmod(angleInRadians, 2 * PI);
	//}
}

int main()
{
	auto game = new GameWindow(WIDTH, HEIGHT, vSource, fSource);

	game->CreateBuffers(vertices, sizeof(vertices), indecies, sizeof(indecies));
	game->CreateBuffers(vertices, sizeof(vertices), indecies, sizeof(indecies));
	game->SetCallback(&Callback);
	game->LoadTexture(container);
	game->LoadTexture(awesomeFace);
	game->Render();

	//void* p = game;
	//auto* pt = new (p) GameWindow(WIDTH, HEIGHT, vSource, fSource); //placement new 
	//pt->~GameWindow();

	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF); //check leak memory

	return 0;
}