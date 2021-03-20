#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Headers.h"
#include "GameWindow.h"

const int WIDTH = 800;
const int HEIGHT = 600;

GLfloat angleInRadians = 0.f;
GLfloat mixValue = 0.2f;

bool keys[1024] = { false };

GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const GLuint indecies[] =
{
	0, 1, 3,
	1, 2, 3
};

const char* vSource = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\OpenGL\\lesson 1.9 - camera\\lesson\\vertex.GLSL";
const char* fSource = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\OpenGL\\lesson 1.9 - camera\\lesson\\fragment.GLSL";
const char* container = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\container.jpg";
const char* awesomeFace = "C:\\Users\\SliceOfKekus\\Documents\\OpenGL\\LearnOpenGL\\awesomeface.png";

void Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
		{
			mixValue = 1.f;
		}
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
		{
			mixValue = 0.f;
		}
	}

	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else
	{
		if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

GLfloat lastX = WIDTH / 2;
GLfloat lastY = HEIGHT / 2;
GLfloat yawAngle = -90.f;
GLfloat pitchAngle = 0.f;
GLfloat fov = 45.0f;

bool firstTryMouse = true;

void ScrollCallback(GLFWwindow* window, double xOffSet, double yOffSet)
{
	fov -= yOffSet;

	if (fov >= 100.f)
		fov = 100.f;
	if (fov <= 1.f)
		fov = 1.f;
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	//use glfwSetCursorPos instead
	if (firstTryMouse)
	{
		lastX = static_cast<GLfloat>(xpos);
		lastY = static_cast<GLfloat>(ypos);
		firstTryMouse = false;
	}

	GLfloat sensitivity = 0.3f;
	GLfloat xOffSet = (static_cast<GLfloat>(xpos) - lastX) * sensitivity;
	GLfloat yOffSet = (static_cast<GLfloat>(ypos) - lastY) * sensitivity;

	lastX = static_cast<GLfloat>(xpos);
	lastY = static_cast<GLfloat>(ypos);

	yawAngle += xOffSet;
	pitchAngle -= yOffSet;
	
	if (pitchAngle >= 90.f)
		pitchAngle = 89.9f;

	if (pitchAngle <= -90.f)
		pitchAngle = -89.9f;
}


int main()
{
	using namespace glm;

	auto game = new GameWindow(WIDTH, HEIGHT, vSource, fSource);

	game->CreateBuffers(vertices, sizeof(vertices), indecies, sizeof(indecies));
	game->LoadTexture(container);
	game->LoadTexture(awesomeFace);
	game->SetKeyCallback(&Callback);
	game->SetMouseCallback(&MouseCallback);
	game->SetScrollCallback(&ScrollCallback);
	game->Render();

	//orthographic projection 
	//mat4 ort = ortho(0.f, 800.f, 0.f, 600.f, 0.1f, 100.f);
	//not realistic images

	//perpsective projection
												//fov   //Display aspect ratio       //near plane //far plane
	//mat4 pers = perspective(45.f, static_cast<float>(WIDTH) / HEIGHT, 0.1f, 100.f);

	//multiplication in 
	//vec4 Vclip = projectionMatrix * viewMatrix * modelMatrix * Vlocal;

	return 0;
}