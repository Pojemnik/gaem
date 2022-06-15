#include "rigidbody.h"

Rigidbody::Rigidbody(float mass, float gravity, Transform& transform)
	: Component(transform), _mass(mass), _gravity(gravity)
{
}

void Rigidbody::update(float dt, const std::vector<Collider>& colliders)
{

}
