#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "Globals.h"
#include "DebugUtil.h"
#include "Shader.h"
#include "Camera.h"
#include "EventSystem.h"
#include "Model.h"

int main(int argc, char** argv)
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cerr << "GLFW init error. GLFW Error: " << GetGlfwError() << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	g_Window = glfwCreateWindow(g_WindowWidth, g_WindowHeight, "Rotating Model", nullptr, nullptr);
	if (!g_Window)
	{
		std::cerr << "GLFW Window error. GLFW Error: " << GetGlfwError() << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(g_Window);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(g_Window, [](GLFWwindow* window, int width, int height)
		{
			g_WindowWidth = width;
			g_WindowHeight = height;

			std::cout << g_WindowWidth << " : " << g_WindowHeight << std::endl;
		});

	GLenum _glewInit = glewInit();
	if (_glewInit != GLEW_OK)
	{
		std::cerr << "GLEW init error. GLEW Error: " << glewGetErrorString(_glewInit) << std::endl;
		return -1;
	}

	// GL Enables
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glfwSetKeyCallback(g_Window, [](GLFWwindow* window, int key,
		int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				g_OnKeyDown.Dispatch(key);
				break;

			case GLFW_RELEASE:
				g_OnKeyUp.Dispatch(key);
				break;

			case GLFW_REPEAT:
				g_OnKeyHold.Dispatch(key);
				break;
			}
		});

	g_RessourceManager = std::make_unique<RessourceManager>();

	Camera _camera = Camera();

	Shader _shader("res/shader.vert", "res/shader.frag");
	_shader.Bind();

	Model* _model = new Model("res/backpack.obj");

	while (!glfwWindowShouldClose(g_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_camera.Update(_shader);
		_model->Render(_shader);

		glfwSwapBuffers(g_Window);
		glfwPollEvents();
	}

	return 0;
}