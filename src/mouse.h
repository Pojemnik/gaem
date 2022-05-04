#pragma once
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "definitions.h"

class Mouse
{
private:
	inline static vec2 _cursorPosition = vec2(0);
	inline static vec2 _cursorDelta = vec2(0);
	inline static bool _isCursorLocked = false;

public:
	void static lockCursor(GLFWwindow* window);
	void static unlockCursor(GLFWwindow* window);
	void static cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void static mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static vec2 getCursorPosition();
	static vec2 getCursorDelta();
};

