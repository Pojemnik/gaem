#pragma once
#include <glm.hpp>

#include <memory>
#include <string>

#include "definitions.h"
#include "shader.h"
#include "vertexArray.h"

class DrawableObject
{
private:
	mat4 _matrix;
	const VertexArray _vertexArray;

public:
	DrawableObject(std::string file);
	void rotate(float angle, vec3 axis);
	void rotateDeg(float angle, vec3 axis);
	void move(vec3 direction);
	void scale(vec3 coef);
	void draw(const Shader& shader);
};

