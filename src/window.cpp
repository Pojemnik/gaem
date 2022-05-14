#include "window.h"

Window::Window(glm::ivec2 size, std::string name) : _size(size),
	_window(glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL))
{
	if (_window == nullptr)
	{
		std::cerr << "Window creation error" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(_window);
	glViewport(0, 0, size.x, size.y);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}

GLFWwindow* Window::getWindow() const
{
	return _window;
}
