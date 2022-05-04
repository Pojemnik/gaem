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
	if (_listeners.find(key) != _listeners.end())
	{
		if (action == GLFW_PRESS)
		{
			for (const auto& v : _listeners[key])
			{
				v.second();
			}
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

void Keyboard::addKeyPressedListener(int key, const std::string& id, std::function<void()> listener)
{
	if (_listeners.find(key) == _listeners.end())
	{
		_listeners.insert({ key, {} });
	}
	_listeners[key].insert({id, listener });
}

void Keyboard::removeKeyPressedListener(int key, const std::string& id)
{
	if (_listeners.find(key) == _listeners.end())
	{
		std::cerr << "Removing key listener:\nNo listner registered for the key " << key << std::endl;
		return;
	}
	if (_listeners[key].find(id) == _listeners[key].end())
	{
		std::cerr << "Removing key listener:\nNo listner registered with the id " << id << std::endl;
		return;
	}
	_listeners[key].erase(id);
}
