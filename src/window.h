#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <string>
#include <iostream>

#include "definitions.h"

class Window
{
private:
	GLFWwindow* _window;
	glm::ivec2 _size;

public:
	Window(glm::ivec2 size, std::string name);
	~Window();
	GLFWwindow* getWindow() const;
	glm::ivec2 getSize() const;
};

