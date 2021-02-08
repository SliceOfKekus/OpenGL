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
	"  gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
	"}\0";
const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"  color = vec4(1.0f, 0.f, 0.f, 1.0f);\n"
	"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void GenBuffers(GLuint* VAO, GLuint* VBO, GLfloat* vertices, size_t size)
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "heya o/", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "ERROR::GLFW::WIN_CREATION_FAILED\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "ERROR::GLEW::INITIALIZATION_FAILED\n";
		std::cout << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLint success;
	GLchar log[512];
	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!(success))
	{
		glGetProgramInfoLog(vertexShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
		glfwTerminate();
		return -1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!(success))
	{
		glGetProgramInfoLog(fragmentShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
		glfwTerminate();
		return -1;
	}

	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(log), nullptr, log);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << log << std::endl;
		glfwTerminate();
		return -1;
	}

	GLfloat firstTriangle[] = {
		-1.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};

	GLfloat secondTriangle[] = {
		 0.0f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 1.0f, -0.5f, 0.0f
	};

	GLuint f_VBO, f_VAO, s_VBO, s_VAO;
	
	GenBuffers(&f_VAO, &f_VBO, firstTriangle, sizeof(firstTriangle));
	GenBuffers(&s_VAO, &s_VBO, secondTriangle, sizeof(secondTriangle));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(f_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(s_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &f_VAO);
	glDeleteBuffers(1, &f_VBO);
	glDeleteVertexArrays(1, &s_VAO);
	glDeleteBuffers(1, &s_VBO);

	glfwTerminate();
	return 0;
}