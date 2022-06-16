#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include "definitions.h"
#include "collider.h"
#include "drawableObject.h"
#include "transform.h"

class Rigidbody
{
private:
	float _gravity;
	vec3 _velocity = vec3(0,0,0);
	bool _isColliding = false;

public:
	Rigidbody(float gravity);
	void update(float dt, const std::vector<Collider*>& colliders, Transform& transform);
	void addVelocity(vec3 value);
	bool isColliding() const;
};