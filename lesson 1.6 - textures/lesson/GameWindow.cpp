#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const char* vSource, const char* fSource)
	: window(nullptr)
	, program()
	, texture()
	, VAO(0), VBO(0), IBO(0)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "heya o/", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	glewInit();
	glViewport(0, 0, width, height);

	program.Load(vSource, fSource);
}

void GameWindow::CreateBuffers(const GLfloat* v, GLsizeiptr vSize,
															 const GLuint* i, GLsizeiptr iSize)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vSize, v, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, i, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
}

void GameWindow::LoadTexture(const char* tSource) const noexcept
{
	int width, height;
	unsigned char* image = SOIL_load_image(tSource, &width, &height, 0, SOIL_LOAD_RGB);

	texture.push_back(0);

	glGenTextures(1, &texture[texture.size() - 1]);
	glBindTexture(GL_TEXTURE_2D, texture[texture.size() - 1]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameWindow::Render()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		program.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(program.GetIndex(), "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glUniform1i(glGetUniformLocation(program.GetIndex(), "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(program.GetIndex(), "mixValue"), mixValue);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glfwTerminate();
}

void GameWindow::SetCallback(void(*func)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(window, func);
}

GameWindow::~GameWindow()
{}
