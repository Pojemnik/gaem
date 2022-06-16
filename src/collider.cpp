#include "collider.h"

Collider::Collider(vec3 halfExtend, vec3 position) :
	_up(position.y + halfExtend.y),
	_down(position.y - halfExtend.y),
	_right(position.x + halfExtend.x),
	_left(position.x - halfExtend.x),
	_front(position.z + halfExtend.z),
	_back(position.z - halfExtend.z) {}

void Collider::move(vec3 delta)
{
	_up += delta.y;
	_down += delta.y;
	_right += delta.x;
	_left += delta.x;
	_front += delta.z;
	_back += delta.z;
}

bool Collider::collides(vec3 point) const
{
	if (point.x > _right)
	{
		return false;
	}
	if (point.x < _left)
	{
		return false;
	}
	if (point.y > _up)
	{
		return false;
	}
	if (point.y < _down)
	{
		return false;
	}
	if (point.z > _front)
	{
		return false;
	}
	if (point.z < _back)
	{
		return false;
	}
	return true;
}

vec3 Collider::solveY(vec3 point) const
{
	vec3 result = point;
	result.y = _up;
	return result;
}
