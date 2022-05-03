#pragma once
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

class Keyboard
{
private:
	inline static std::map<int, bool> _trackedKeysState;

public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool isKeyPressed(int key);
	static void addTrackedKey(int index);
	static void addTrackedKeys(const std::vector<int>& indexes);
	static void clearKeyPresses();
};