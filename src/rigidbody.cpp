#include "rigidbody.h"

Rigidbody::Rigidbody(float gravity)
	: _gravity(gravity)
{
}

void Rigidbody::update(float dt, const std::vector<Collider*>& colliders, Transform& transform)
{
	vec3 currentPos = transform.getPosition();
	_velocity += vec3(0, -_gravity * dt, 0);
	vec3 nextPos = currentPos + _velocity;
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
	//std::cout << "Velocity: " << _velocity << std::endl;
	transform.moveTo(nextPos);
}

void Rigidbody::addVelocity(vec3 value)
{
	_velocity += value;
}

bool Rigidbody::isColliding() const
{
	return _isColliding;
}
