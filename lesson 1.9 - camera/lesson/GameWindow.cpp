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
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(width, height, "heya o/", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
	
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

	glEnable(GL_DEPTH_TEST);

	vec3 cameraPos(0.f, 0.f, 3.0f);
	vec3 cameraFront(0.f, 0.f, -1.f);
	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;

	while (!glfwWindowShouldClose(window))
	{
		glm::vec3 cubePositions[] = 
		{
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glfwPollEvents();

		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(program.GetIndex(), "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glUniform1i(glGetUniformLocation(program.GetIndex(), "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(program.GetIndex(), "mixValue"), mixValue);
		
		//mat4 view(1.0f);
		mat4 projection(1.0f);
		GLint width, height;
		
		glfwGetFramebufferSize(window, &width, &height);		
		//view = translate(view, vec3(0.f, 0.f, -3.0f));
		projection = perspective(radians(fov), static_cast<float>(800) / 600, 0.1f, 100.0f);
		
		//glUniformMatrix4fv(glGetUniformLocation(program.GetIndex(), "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program.GetIndex(), "projection"), 1, GL_FALSE, value_ptr(projection));
		
		//vec3 cameraPos(0.f, 0.f, 3.0f);
		//vec3 cameraTarget(0.f, 0.f, 0.f);
		//vec3 cameraDirectionZ = normalize(cameraPos - cameraTarget);
		//
		//vec3 directionY(0.f, 1.0f, 0.f);
		//vec3 cameraDirectionX = normalize(cross(directionY, cameraDirectionZ));
		//vec3 cameraDirectionY = normalize(cross(cameraDirectionZ, cameraDirectionX));

		//mat4 viewMatrix;
		//
		//viewMatrix = lookAt(cameraPos,
		//										cameraTarget,
		//										directionY
		//									  );
		//
		////making rotating scene
		//GLfloat radius = 10.f;
		//GLfloat camX = static_cast<GLfloat>(sin(glfwGetTime()) * 10.f);
		//GLfloat camZ = static_cast<GLfloat>(cos(glfwGetTime()) * 10.f);
		//viewMatrix = lookAt(vec3(camX, 0.f, camZ),
		//										cameraTarget,
		//										directionY);
		//

		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLfloat cameraSpeed = 5.f * deltaTime;
		mat4 view(1.0f);
		vec3 cameraUp(0.f, 1.f, 0.f);

		vec3 front;
		
		front.x = cos(radians(pitchAngle)) * cos (radians(yawAngle));
		front.y = sin(radians(pitchAngle));
		front.z = cos(radians(pitchAngle)) * sin(radians(yawAngle));

		cameraFront = normalize(front);

		if (keys[GLFW_KEY_W])
		{
			cameraPos += cameraSpeed * cameraFront;
		}
		if (keys[GLFW_KEY_S])
		{
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (keys[GLFW_KEY_A])
		{
			cameraPos += normalize(cross(cameraUp, cameraFront)) * cameraSpeed;
		}
		if (keys[GLFW_KEY_D])
		{
			cameraPos -= normalize(cross(cameraUp, cameraFront)) * cameraSpeed;
		}
		if (keys[GLFW_KEY_SPACE])
		{
			cameraPos += cameraSpeed * cameraUp;
		}
		if (keys[GLFW_KEY_TAB])
		{
			cameraPos -= cameraSpeed * cameraUp;
		}

		view = lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

		glBindVertexArray(VAO[0]);
		
		for (GLuint i = 0; i < 10; ++i)
		{
			//mat4 viewMatrix;
			//GLfloat radius = 3.f;
			//GLfloat camX = static_cast<GLfloat>(sin(glfwGetTime()) * radius);
			//GLfloat camZ = static_cast<GLfloat>(cos(glfwGetTime()) * radius);
			//viewMatrix = lookAt(vec3(camX, 0.f, camZ),
			//	cameraTarget,
			//	directionY);

			mat4 model(1.0f);
			
			model = translate(model, cubePositions[i]);

			if (!(i % 3))
				model = rotate(model, radians(static_cast<float>(glfwGetTime()) * 50.f), vec3(1.0f, 1.0f, 0.f));
			else
				model = rotate(model, radians(20.f * i), vec3(1.0f, 1.0f, 0.f));
		
			glUniformMatrix4fv(glGetUniformLocation(program.GetIndex(), "view"), 1, GL_FALSE, value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(program.GetIndex(), "model"), 1, GL_FALSE, value_ptr(model));
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
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

void GameWindow::SetKeyCallback(void(*func)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(window, func);
}

void GameWindow::SetMouseCallback(void(*func)(GLFWwindow*, double, double))
{
	glfwSetCursorPosCallback(window, func);
}

void GameWindow::SetScrollCallback(void(*func)(GLFWwindow*, double, double))
{
	glfwSetScrollCallback(window, func);
}

GameWindow::~GameWindow()
{}

