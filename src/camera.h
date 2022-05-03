#pragma once
#include <glm.hpp>

#include "definitions.h"
#include "shader.h"

class Camera
{
private:
	mat4 _view;
	mat4 _perspective;

	vec3 _position;
	vec3 _target;
	vec3 _up;
	float _fov;
	float _aspect;
	float _near;
	float _far;

	bool _recalcNeeded = false;

	void recalc();

public:
	Camera(vec3 position, vec3 target, float fov, float aspect, float near, float far, vec3 up = vec3(0,1,0));
	void update(const Shader& shader);
	void moveWithTarget(vec3 delta);
};

