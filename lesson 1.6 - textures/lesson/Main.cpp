#include <iostream>

#include "Headers.h"
#include "GameWindow.h"

const int WIDTH = 1200;
const int HEIGHT = 1000;

const GLfloat vertices[] = 
{
	 // Позиции						// Цвета            // Текстурные координаты
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
};

const GLuint indecies[] =
{
	0, 1, 3,
	1, 2, 3
};

const char* vSource = "C:\\Users\\SliceOfKekus\\Desktop\\vertex.GLSL";
const char* fSource = "C:\\Users\\SliceOfKekus\\Desktop\\fragment.GLSL";
const char* container = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\container.jpg";
const char* awesomeFace = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\awesomeface.png";

GLfloat mixValue = 0.2f;

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
}

int main()
{
	GameWindow game(WIDTH, HEIGHT, vSource, fSource);

	game.CreateBuffers(vertices, sizeof(vertices), indecies, sizeof(indecies));
	game.SetCallback(&Callback);
	game.LoadTexture(container);
	game.LoadTexture(awesomeFace);
	game.Render();

	return 0;
}