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
	float _friction;
	float _maxHorizontalVelocity;
	void applyFriction(float dt);

public:
	Rigidbody(float gravity, float friction, float maxHorizontalVelocity);
	void update(float dt, const std::vector<Collider*>& colliders, Transform& transform);
	void addVelocity(vec3 value);
	bool isColliding() const;
};