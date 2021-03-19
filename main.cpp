#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>//<xxx> -> 系统库
#include "Shader.h"//”xxx“ -> 自定义库

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

float vertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
//0,1,2  2,1,3

//EBO
unsigned int indices[] = {
	0, 1, 2, // 第一个三角形
	2, 3, 0  // 第二个三角形
};

glm::vec3 cubePositions[] = {
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[])
{

	//int index = 1;
	//int index1 = 2;
	//int* i = &index;
	//cout << i << endl;
	//cout << &i << endl;
	//cout << *i << endl;
	//cout << index << endl;
	//cout << &index << endl;
	//*i = index1;
	//cout <<"----------------" << endl;
	//cout << i << endl;
	//cout << &i << endl;
	//cout << *i << endl;
	//cout << index << endl;
	//cout << &index << endl;
	//i = &index1;
	//cout << "----------------" << endl;
	//cout << i << endl;
	//cout << &i << endl;
	//cout << *i << endl;
	//cout << index << endl;
	//cout << &index << endl;
	
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
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);//正面 GL_FRONT
	//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//ZTest
	glEnable(GL_DEPTH_TEST);

	//栈
	//Shader testShader = Shader("vertexSource.txt", "fragmentSource.txt");
	//testShader.test();
	//new -> 堆
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	//testShader->test();

	//真正用法
	//unsigned int VAO[10];
	//glGenVertexArrays(1, VAO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//默认逆时针绘制顶点
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
	//glEnableVertexAttribArray(1);
	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannel;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load tex failed");
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load tex2 failed");
	}
	stbi_image_free(data2);

	//计算变换矩阵
	//glm::mat4 trans;
	glm::mat4 trans = glm::mat4(1.0f);
	//平移
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0));

	//旋转                               角度                     旋转轴
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(-1.0f, 0, 0));
	
	//缩放
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));


	//组合 先缩放,再旋转,再平移 这里反着写是因为glm右乘
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//在下一帧开始时处理输入
		processInput(window);

		//render commonder...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//COLOR_BUFFER:显示到屏幕上的buffer

		//glBindTexture(GL_TEXTURE_2D, TexBufferA);//第一张texture默认开启，不需要设置uniform

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);



		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modelRandomMat = glm::mat4(1.0f);
			modelRandomMat = glm::translate(modelRandomMat, cubePositions[i]);

			myShader->use();

			//传递Uniform数据给GPU
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFaceTexture"), 3);
			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"),1, GL_FALSE, glm::value_ptr(trans));

			//一个一个Draw
			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelRandomMat));

			//GPU Instancing
				glm::mat4 modelInstanceMat = glm::mat4(1.0f);
				modelInstanceMat = glm::translate(modelInstanceMat, cubePositions[i]);
				string index = std::to_string(i);
				GLint location = glGetUniformLocation(myShader->ID, ("instanceModelMat[" + index + "]").c_str());
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelInstanceMat));

			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"),1, GL_FALSE, glm::value_ptr(projMat));

			//DrawCall
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			//一个一个Draw
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//GPU Instancing
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10);

		//call event ，交换Buffer
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	glfwTerminate();
	return 0;
}

