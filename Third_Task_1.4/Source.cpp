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
const GLchar* firstFragmentShaderSource =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"  color = vec4(1.0f, 0.f, 0.f, 1.0f);\n"
"}\0";
const GLchar* secondFragmentShaderSource =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"  color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "heya o/", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "ERROR::GLEW::INITIALIZATION_FAILED\n";
		std::cout << glewGetErrorString(err) << "\n";
		return -1;
	}

	int width, height;
	
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLint success;
	GLchar log[512];
	GLuint vertexShader,
		firstFragmentShader,
		secondFragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	firstFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(vertexShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_ERROR\n";
		std::cout << log << "\n";
		return -1;
	}

	glShaderSource(firstFragmentShader, 1, &firstFragmentShaderSource, nullptr);
	glCompileShader(firstFragmentShader);
	glGetShaderiv(firstFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(firstFragmentShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR\n";
		std::cout << log << "\n";
		return -1;
	}

	glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, nullptr);
	glCompileShader(secondFragmentShader);
	glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(secondFragmentShader, sizeof(log), nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR\n";
		std::cout << log << "\n";
		return -1;
	}

	GLuint program = glCreateProgram(), 
				 programYellow = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, firstFragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		std::cout << "ERROR::PROGRAM::LINKING_ERROR\n";
		std::cout << log << "\n";
		return -1;
	}

	glAttachShader(programYellow, vertexShader);
	glAttachShader(programYellow, secondFragmentShader);
	glLinkProgram(programYellow);
	glGetProgramiv(programYellow, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(programYellow, sizeof(log), nullptr, log);
		std::cout << "ERROR::PROGRAM::LINKING_ERROR\n";
		std::cout << log << "\n";
		return -1;
	}

	GLfloat firstTriangle[] = {
				-0.9f, -0.5f, 0.0f,  // Left 
				-0.0f, -0.5f, 0.0f,  // Right
				-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
			 0.0f, -0.5f, 0.0f,  // Left
			 0.9f, -0.5f, 0.0f,  // Right
			 0.45f, 0.5f, 0.0f   // Top 
	};
	GLuint VAOs[2], VBOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//first-triangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//second-triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//first-triangle
		glUseProgram(program);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//second-triangle
		glUseProgram(programYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glfwTerminate();

	return 0;
}

