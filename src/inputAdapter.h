#pragma once
#include <numeric>

#include "camera.h"
#include "definitions.h"

class InputAdapter
{
public:
	inline static bool enabled = true;
	inline static float mouseSensitivity = 25.f;

	static vec2 mouseDeltaToCameraInput(vec2 delta);
};

