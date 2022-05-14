#pragma once
#include <memory>

#include "shader.h"
#include "camera.h"

class Drawable
{
public:
	virtual void draw(const Camera& camera, const Shader& shader) = 0;
};

