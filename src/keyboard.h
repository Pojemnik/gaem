#pragma once
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <functional>
#include <iostream>

class Keyboard
{
private:
	inline static std::map<int, bool> _trackedKeysState;
	inline static std::map<int, std::map<std::string, std::function<void()>>> _listeners;

public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool isKeyPressed(int key);
	static void addTrackedKey(int index);
	static void addTrackedKeys(const std::vector<int>& indexes);
	static void addKeyPressedListener(int key, const std::string& id, std::function<void()> listener);
	static void removeKeyPressedListener(int key, const std::string& id);
};