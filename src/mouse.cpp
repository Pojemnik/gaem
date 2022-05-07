#include "mouse.h"

void Mouse::lockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	_isCursorLocked = true;
	_lockedThisFrame = true;
}

void Mouse::unlockCursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	_isCursorLocked = false;
}

void Mouse::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	
}

void Mouse::updateMousePosition(GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (!_isCursorLocked)
	{
		return;
	}
	if (_lockedThisFrame)
	{
		_lockedThisFrame = false;
	}
	else
	{
		_cursorDelta.x = static_cast<float>(xpos) - _cursorPosition.x;
		_cursorDelta.y = _cursorPosition.y - static_cast<float>(ypos);
	}
	_cursorPosition = vec2(xpos, ypos);
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
