#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.h"
#include<stdio.h>
#include "Window.h"
#include "Shader.h"
#include<stb/stb_image.h>
#include "Texture.h"
#include "VAO.h"
#include "EBO.h"
#include "Mesh.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "LawnGL";

int main()
{

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,  // First triangle
		1, 2, 3   // Second triangle
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	Texture text = Texture("D:\\GraphicsStuff\\LawnGL\\Textures\\aaa.png");
	
	Mesh mesh = Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

	//VAO vao1;
	//vao1.Bind();

	//VBO vbo1(vertices, sizeof(vertices));

	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//
	//EBO ebo1(indices, sizeof(indices));


	//vao1.LinkVBO(vbo1, 0);

	//vao1.Unbind();
	//vbo1.Unbind();
	//ebo1.Unbind();

	//


	while (!glfwWindowShouldClose(currentWindow.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		MyShader.Activate();
		text.Bind();

		mesh.MeshVAO.Bind();
		//vao1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(currentWindow.window);
		glfwPollEvents();
	}

	//vao1.Delete();
	//vbo1.Delete();
	//ebo1.Delete();

	glfwTerminate();

	return 0;
}