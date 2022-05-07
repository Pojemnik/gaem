#pragma once
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>

#include "definitions.h"
#include "util.h"

class Mouse
{
private:
	inline static vec2 _cursorPosition = vec2(0);
	inline static vec2 _cursorDelta = vec2(0);
	inline static bool _isCursorLocked = false;
	inline static bool _lockedThisFrame = false;

public:
	void static lockCursor(GLFWwindow* window);
	void static unlockCursor(GLFWwindow* window);
	void static cursorPositionCallback(GLFWwindow* indow, double xpos, double ypos);
	void static updateMousePosition(GLFWwindow* window);
	void static mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static vec2 getCursorPosition();
	static vec2 getCursorDelta();
};
