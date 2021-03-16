#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include <memory>

//work with texture
#include <SOIL.h>

#include "ShaderProgram.h"
#include "GameWindow.h"


const int WIDTH = 1200;
const int HEIGHT = 1000;

const GLfloat vertices[] = 
{
	 // Позиции						// Цвета            // Текстурные координаты
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // Верхний правый
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // Нижний правый
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // Верхний левый 
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

int main()
{
	GameWindow game(WIDTH, HEIGHT, vSource, fSource);

	game.CreateBuffers(vertices, sizeof(vertices), indecies, sizeof(indecies));
	game.LoadTexture(container);
	game.LoadTexture(awesomeFace);
	game.Render();

	return 0;
}