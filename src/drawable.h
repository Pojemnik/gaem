#pragma once
#include <memory>

#include "shader.h"
#include "camera.h"
#include "definitions.h"

class Drawable
{
public:
	virtual void draw(const Camera& camera, const Shader& shader, vec4 color = vec4(0, 0, 0, 0)) = 0;
};

