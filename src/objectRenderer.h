#pragma once
#include <glm.hpp>

#include <memory>

#include "definitions.h"
#include "shader.h"
#include "model.h"

class ObjectRenderer
{
private:
	mat4 _matrix;
	std::unique_ptr<Model> _model;
	static const float _deg2rad;

public:
	ObjectRenderer(std::unique_ptr<Model> model);
	void rotate(float angle, vec3 axis);
	void rotateDeg(float angle, vec3 axis);
	void move(vec3 direction);
	void scale(vec3 coef);
	void draw(const Shader& shader);
};

