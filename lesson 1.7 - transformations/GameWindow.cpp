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
	VAO.push_back(0);
	VBO.push_back(0);
	IBO.push_back(0);

	glGenVertexArrays(1, &VAO[VAO.size() - 1]);
	glGenBuffers(1, &VBO[VBO.size() - 1]);
	glGenBuffers(1, &IBO[IBO.size() - 1]);

	glBindVertexArray(VAO[VAO.size() - 1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[VBO.size() - 1]);
	glBufferData(GL_ARRAY_BUFFER, vSize, v, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[IBO.size() - 1]);
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
	using namespace glm;

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

		//transformation
		mat4 transform(1.0f);
		GLuint transformLoc = glGetUniformLocation(program.GetIndex(), "transformMatrix");

		transform = translate(transform, vec3(0.5f, -0.5f, 0.f));
		transform = rotate(transform, static_cast<GLfloat>(sin(glfwGetTime())) * 10.f, vec3(0.f, 0.f, 1.f));

		//transform = rotate(transform, angleInRadians, vec3(0.f, 0.f, 1.f));
		//transform = scale(transform, vec3(0.5f, 0.5f, 0.5f));

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));
		
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GLfloat scaleCoeff = static_cast<GLfloat>(sin(glfwGetTime()));

		transform = mat4(1.f);
		transform = translate(transform, vec3(-0.5f, 0.5f, 0.f));
		transform = scale(transform, vec3(scaleCoeff, scaleCoeff, scaleCoeff));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));

		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		

		glfwSwapBuffers(window);
	}

	for (auto& obj : VAO)
		glDeleteVertexArrays(1, &obj);
	for (auto& obj : VBO)
	glDeleteBuffers(1, &obj);
	for (auto& obj : IBO)
	glDeleteBuffers(1, &obj);

	glfwTerminate();
}

void GameWindow::SetCallback(void(*func)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(window, func);
}

GameWindow::~GameWindow()
{}
