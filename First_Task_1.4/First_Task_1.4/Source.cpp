#include <iostream>

//GLEW
#define GLEW_STATIC
#include <glew.h>

//GLFW
#include <glfw3.h>

//SHADERS
const GLchar* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
	"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint BuildVertexShader()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	GLchar log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(vertexShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	}

	return vertexShader;
}

GLuint BuildFragmentShader()
{
	GLuint framgentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(framgentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(framgentShader);

	GLint success;
	GLchar log[512];
	glGetShaderiv(framgentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(framgentShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	}

	return framgentShader;
}

int main()
{
	glfwInit();
	//set-up all required options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* win = glfwCreateWindow(800, 600, "Heya o/", nullptr, nullptr);

	if (win == nullptr)
	{
		std::cout << "ERROR::GLFW::WINDOW'S_CREATION_FAILED\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	glfwSetKeyCallback(win, key_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "ERROR::GLFW::WINDOW'S_CREATION_FAILED\n";
		std::cout << glewGetErrorString(err) << std::endl;
		return -1;
	}

	//set Viewport
	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	glViewport(0, 0, width, height);

	GLuint vertexShader = BuildVertexShader(),
				 fragmentShader = BuildFragmentShader();
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	GLchar log[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
		return -1;
	}

	GLfloat vertices[] = {
		//first triangle
		-1.0f, -0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f, 
		 0.0f, -0.5f, 0.0f,
		 //second triangle
		 0.5f,  0.5f, 0.0f, 
		 1.0f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f 
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//game loop
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		glfwSwapBuffers(win);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}