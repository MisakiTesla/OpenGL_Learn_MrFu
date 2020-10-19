#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Test.h"

using namespace std;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.8f,0.8f,0.0f
};

const char* vertexShaderSource =
"#version 330 core                                               \n"
"layout(location = 0) in vec3 aPos;                     \n"
"void main() {	\n"
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\n";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[])
{
	int index = 1;
	int index1 = 2;
	int* i = &index;
	cout << i << endl;
	cout << &i << endl;
	cout << *i << endl;
	cout << index << endl;
	cout << &index << endl;
	*i = index1;
	cout <<"----------------" << endl;
	cout << i << endl;
	cout << &i << endl;
	cout << *i << endl;
	cout << index << endl;
	cout << &index << endl;
	i = &index1;
	cout << "----------------" << endl;
	cout << i << endl;
	cout << &i << endl;
	cout << *i << endl;
	cout << index << endl;
	cout << &index << endl;
	
	//cout << &(&vertexShaderSource);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test window ", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "open window failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;

	}

	glfwMakeContextCurrent(window);

	///======================

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, 800, 600);

	//背面剔除
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);//正面 GL_FRONT

	//真正用法
	//unsigned int VAO[10];
	//glGenVertexArrays(1, VAO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//在下一帧开始时处理输入
		processInput(window);

		//render commonder...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//COLOR_BUFFER:显示到屏幕上的buffer

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//call event ，交换Buffer
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	glfwTerminate();
	return 0;
}

