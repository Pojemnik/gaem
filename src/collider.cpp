#include "collider.h"

Collider::Collider(vec3 halfExtend, Transform& transform) :
	_halfExtend(halfExtend), Component(transform)
{
}

vec3 Collider::getHalfExtend() const
{
	return _halfExtend;
}
