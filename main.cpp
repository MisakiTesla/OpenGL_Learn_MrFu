#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>//<xxx> -> 系统库
#include "Shader.h"//”xxx“ -> 自定义库
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"
#include "main.h"

using namespace std;

#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
#pragma endregion

#pragma region Camera Declare

//Instantiate Camera Class
//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, -1.0f, 0), glm::vec3(0, 1.0f, 0));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
//Instantiate Light Class
LightDirectional lightD = LightDirectional(
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));
//LightPoint lightP0 = LightPoint(
//	glm::vec3(1.0f, 0, 0),
//	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
//	glm::vec3(1.0f, 0, 0));
//LightPoint lightP1 = LightPoint(
//	glm::vec3(0, 1.0f, 0),
//	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
//	glm::vec3(0, 1.0f, 0));
//LightPoint lightP2 = LightPoint(
//	glm::vec3(0, 0, 1.0f),
//	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
//	glm::vec3(0, 0, 1.0f));
//LightPoint lightP3 = LightPoint(
//	glm::vec3(1.0f, 1.0f, 1.0f),
//	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
//	glm::vec3(1.0f, 1.0f, 1.0f));
LightPoint lightPs[4]{  
	LightPoint(
	glm::vec3(1.0f, 0, 0),
	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
	glm::vec3(1.0f, 0, 0)),
	LightPoint(
	glm::vec3(0, 1.0f, 0),
	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
	glm::vec3(0, 1.0f, 0)),
	LightPoint(
	glm::vec3(0, 0, 1.0f),
	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
	glm::vec3(0, 0, 1.0f)),
	LightPoint(
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0), glm::radians(45.0), 0),
	glm::vec3(1.0f, 1.0f, 1.0f)) };

LightSpot lightS(
	glm::vec3(0, 8.0f, 0),
	glm::vec3(glm::radians(90.0), glm::radians(0.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion

#pragma region Input Declare
float lastX;
float lastY;
bool isFirstMouse = true;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
	}
	else
	{
		camera.speedZ = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -1.0f;
	}
	else
	{
		camera.speedX = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.speedY = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.speedY = 1.0f;
	}
	else
	{
		camera.speedY = 0;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (isFirstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(deltaX, deltaY);
	printf("%f \n", deltaX);
}
#pragma endregion

unsigned int LoadTextureToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, texBuffer);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load tex failed");
	}
	stbi_image_free(data);
	return texBuffer;
}

int main(int argc, char* argv[])
{
#pragma region Open a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Wunder Engine ", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "open window failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	//关闭鼠标显示
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

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
#pragma endregion

#pragma region Init Shader Program
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	//testShader->test();
#pragma endregion

#pragma region Init Material
	Material* myMaterial = new Material(
		myShader,
		LoadTextureToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		LoadTextureToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		glm::vec3(1.0f, 1.0f, 1.0f),
		64.0f);
#pragma endregion

#pragma region Init and load Models to VAO,VBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//默认逆时针绘制顶点
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(3);
#pragma endregion

#pragma region Init and load Textures

	//unsigned int TexBufferA;
	//TexBufferA = LoadTextureToGPU("container.jpg",GL_RGB,GL_RGB,0);

	//unsigned int TexBufferB;
	//TexBufferB = LoadTextureToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
#pragma endregion

#pragma region Prepare MVP matrices
	//计算变换矩阵
	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
#pragma endregion

#pragma region Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//在下一帧开始时处理输入
		processInput(window);

		//清屏
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//COLOR_BUFFER:显示到屏幕上的buffer


		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++)
		{
			//Set Model matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//Set View matrix
			//Set Projection matrix

			//Set material -> Shader Program
			myShader->use();

			//Set Material -> Textures
			//glBindTexture(GL_TEXTURE_2D, TexBufferA);//第一张texture默认开启，不需要设置uniform
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			//glActiveTexture(GL_TEXTURE0 + 1);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->specular);

			//Set Material -> Uniforms 传递Uniform数据给GPU
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFaceTexture"), 3);
			//一个一个Draw
			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			//GPU Instancing
			glm::mat4 modelInstanceMat = glm::mat4(1.0f);
			modelInstanceMat = glm::translate(modelInstanceMat, cubePositions[i]);
			string index = std::to_string(i);
			GLint location = glGetUniformLocation(myShader->ID, ("instanceModelMat[" + index + "]").c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelInstanceMat));

			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"),1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);

			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			myMaterial->shader->SetUniform3f("lightD.pos", lightD.position);
			myMaterial->shader->SetUniform3f("lightD.color", lightD.color);
			myMaterial->shader->SetUniform3f("lightD.dirToLight", lightD.lightDir);

			for (int j = 0; j < 4; j++)
			{
				string lightIndex = std::to_string(j);
				myMaterial->shader->SetUniform3f(("lightP" + lightIndex +".pos").c_str(), lightPs[j].position);
				myMaterial->shader->SetUniform3f(("lightP" + lightIndex + ".color").c_str(), lightPs[j].color);
				myMaterial->shader->SetUniform3f(("lightP" + lightIndex + ".dirToLight").c_str(), lightPs[j].lightDir);
				myMaterial->shader->SetUniform1f(("lightP" + lightIndex + ".constant").c_str(), lightPs[j].constant);
				myMaterial->shader->SetUniform1f(("lightP" + lightIndex + ".linear").c_str(), lightPs[j].linear);
				myMaterial->shader->SetUniform1f(("lightP" + lightIndex + ".quadratic").c_str(), lightPs[j].quadratic);
			}

			myMaterial->shader->SetUniform3f("lightS.pos", lightS.position);
			myMaterial->shader->SetUniform3f("lightS.color", lightS.color);
			myMaterial->shader->SetUniform3f("lightS.dirToLight", lightS.lightDir);
			myMaterial->shader->SetUniform1f("lightS.constant", lightS.constant);
			myMaterial->shader->SetUniform1f("lightS.linear", lightS.linear);
			myMaterial->shader->SetUniform1f("lightS.quadratic", lightS.quadratic);
			myMaterial->shader->SetUniform1f("lightS.cosPhyInner", lightS.cosPhyInner);
			myMaterial->shader->SetUniform1f("lightS.cosPhyOutter", lightS.cosPhyOutter);


			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

			//Set Model
			glBindVertexArray(VAO);

			//DrawCall 一个一个Draw
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//DrawCall GPU Instancing
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10);

		//Clean up, prepare for next render loop event 交换Buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPos();
	}
#pragma endregion

	//Exit program
	glfwTerminate();
	return 0;
}

