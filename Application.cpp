#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.h"
#include<stdio.h>
#include "Window.h"
#include "Shader.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "LawnGL";

int main()
{
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.1f, 0.2f, 1.0f); \n"
		"}\0";


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Window currentWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		return -1;
	}
	glViewport(0, 0, 800, 600);


	Shader MyShader = Shader("D:\\GraphicsStuff\\LawnGL\\default.vert", "D:\\GraphicsStuff\\LawnGL\\default.frag");

	unsigned int VAO, VBO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//unsigned int vertexShader, fragmentShader, shaderProgram;

	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);

	//glLinkProgram(shaderProgram);


	while (!glfwWindowShouldClose(currentWindow.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		MyShader.Activate();

		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(currentWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}