#pragma once
#include <memory>

#include "definitions.h"

class Collider
{
private:
	float _up;
	float _down;
	float _right;
	float _left;
	float _front;
	float _back;

public:
	Collider(vec3 halfExtend, vec3 position);
	void move(vec3 delta);
	bool collides(vec3 point) const;
	vec3 solveY(vec3 point) const;
};

