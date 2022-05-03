#include "keyboard.h"

void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (_trackedKeysState.find(key) != _trackedKeysState.end())
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			_trackedKeysState[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			_trackedKeysState[key] = false;
		}
	}
}

bool Keyboard::isKeyPressed(int key)
{
	return _trackedKeysState[key];
}

void Keyboard::addTrackedKey(int index)
{
	if (_trackedKeysState.find(index) == _trackedKeysState.end())
	{
		_trackedKeysState.insert({ index, false });
	}
}

void Keyboard::addTrackedKeys(const std::vector<int>& indexes)
{
	for (int i : indexes)
	{
		addTrackedKey(i);
	}
}

void Keyboard::clearKeyPresses()
{
	for (auto& element : _trackedKeysState)
	{
		element.second = false;
	}
}