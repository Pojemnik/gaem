#include "rigidbody.h"

void Rigidbody::applyFriction(float dt)
{
	vec3 horizontalVelocity = vec3(_velocity.x, 0, _velocity.z);
	if (glm::length(horizontalVelocity) <= _friction * dt)
	{
		horizontalVelocity = vec3(0, 0, 0);
	}
	else
	{
		horizontalVelocity -= glm::normalize(horizontalVelocity) * _friction * dt;
	}
	_velocity = horizontalVelocity + vec3(0, _velocity.y, 0);
}

Rigidbody::Rigidbody(float gravity, float friction, float maxHorizontalVelocity)
	: _gravity(gravity), _friction(friction), _maxHorizontalVelocity(maxHorizontalVelocity)
{
}

void Rigidbody::update(float dt, const std::vector<Collider*>& colliders, Transform& transform)
{
	vec3 currentPos = transform.getPosition();
	applyFriction(dt);
	_velocity += vec3(0, -_gravity * dt, 0);
	vec3 nextPos = currentPos + _velocity * dt;
	_isColliding = false;
	for (const auto& it : colliders)
	{
		if (it->collides(nextPos))
		{
			nextPos = it->solveY(nextPos);
			_velocity.y = 0;
			_isColliding = true;
			break;
		}
	}
	transform.moveTo(nextPos);
}

void Rigidbody::addVelocity(vec3 value)
{
	vec3 horizontal = vec3(_velocity.x, 0, _velocity.z);
	horizontal += vec3(value.x, 0, value.z);
	if (glm::length(horizontal) > _maxHorizontalVelocity)
	{
		horizontal = glm::normalize(horizontal) * _maxHorizontalVelocity;
	}
	_velocity = horizontal + vec3(0, _velocity.y + value.y, 0);
}

bool Rigidbody::isColliding() const
{
	return _isColliding;
}
