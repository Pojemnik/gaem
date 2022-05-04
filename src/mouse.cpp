#include "mouse.h"

void Mouse::lockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void Mouse::unlockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Mouse::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 newPos = glm::vec2(xpos, ypos);
	_cursorDelta = newPos - _cursorPosition;
	_cursorPosition = newPos;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

vec2 Mouse::getCursorPosition()
{
	return _cursorPosition;
}

vec2 Mouse::getCursorDelta()
{
	return _cursorDelta;
}
