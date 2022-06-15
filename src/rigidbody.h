#pragma once
#include <vector>
#include <memory>

#include "definitions.h"
#include "collider.h"
#include "drawableObject.h"
#include "component.h"
#include "transform.h"

class Rigidbody : public Component
{
private:
	float _mass;
	float _gravity;

public:
	Rigidbody(float mass, float gravity, Transform& transform);
	void update(float dt, const std::vector<Collider>& colliders);
};