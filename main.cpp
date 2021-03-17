#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

float vertices[] = {
	//位置				//颜色
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,//0
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//1
	0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,//2
	//0.5f, -0.5f, 0.0f,
	//0.0f, 0.5f, 0.0f,
	0.8f,0.8f,0.0f, 1.0f, 0, 1.0f//3
};
//0,1,2  2,1,3

//EBO
unsigned int indices[] = {
	0, 1, 2, // 第一个三角形
	2, 1, 3  // 第二个三角形
};

const char* vertexShaderSource =
"#version 330 core                                               \n"
"layout(location = 0) in vec3 aPos;					        \n"
"layout(location = 1) in vec3 aColor;					    \n"
"out vec4 vertexColor;                                           \n"
"void main() {														\n"
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"//最后一位齐次坐标 -> 1-标量，0-向量
"		vertexColor = vec4(aColor.x , aColor.y, aColor.z, 1.0);                           \n"
"}																			\n";

const char* fragmentShaderSource =
"#version 330 core										\n"
"out vec4 FragColor;										\n"
"in vec4 vertexColor;										\n"
"uniform vec4 ourColor;										\n"
"void main(){													\n"
"    FragColor = vertexColor;							\n"
"}																	\n";

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
	glCullFace(GL_BACK);//正面 GL_FRONT
	//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//真正用法
	//unsigned int VAO[10];
	//glGenVertexArrays(1, VAO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//默认逆时针绘制顶点
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	cout << VBO << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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

	//位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//在下一帧开始时处理输入
		processInput(window);

		//render commonder...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//COLOR_BUFFER:显示到屏幕上的buffer

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//call event ，交换Buffer
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	glfwTerminate();
	return 0;
}

