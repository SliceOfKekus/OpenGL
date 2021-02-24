#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "ShaderProgram.h"

const char* vSource = "C:\\Users\\SliceOfKekus\\Desktop\\vertex.GLSL";
const char* fSource = "C:\\Users\\SliceOfKekus\\Desktop\\fragment.GLSL";
const GLint WIDHT = 1200;
const GLint HEIGHT = 1000;

const GLfloat vertices[] =
{
  0.5f, -0.5f, 0.0f,
 -0.5f, -0.5f, 0.0f,
  0.0f,  0.5f, 0.0f
};

void EscapeProgram(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDHT, HEIGHT, "heya o/", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, EscapeProgram);

	glewInit();
	glViewport(0, 0, WIDHT, HEIGHT);

	ShaderProgram program(vSource, fSource);
	GLuint VAO, VBO;

	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		program.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}