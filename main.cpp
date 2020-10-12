#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[])
{
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

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//在下一帧开始时处理输入
		processInput(window);

		//render commonder...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//COLOR_BUFFER:显示到屏幕上的buffer

		//call event ，交换Buffer
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	glfwTerminate();
	return 0;
}

