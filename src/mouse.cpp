#include "mouse.h"

void Mouse::lockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	_isCursorLocked = true;
}

void Mouse::unlockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	_isCursorLocked = false;
}

void Mouse::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 newPos = glm::vec2(xpos, ypos);
	_cursorDelta = newPos - _cursorPosition;
	_cursorPosition = newPos;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (!_isCursorLocked)
		{
			lockCursor(window);
		}
	}
}

vec2 Mouse::getCursorPosition()
{
	return _cursorPosition;
}

vec2 Mouse::getCursorDelta()
{
	return _cursorDelta;
}
