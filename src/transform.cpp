#include "transform.h"

Transform::Transform(vec3 position, std::shared_ptr<DrawableObject> drawable, std::shared_ptr<Collider> collider)
	: _drawable(drawable), _collider(collider), Component(*this)
{
	_drawable->move(position);
}

void Transform::moveRelative(vec3 vector)
{
	_position += vector;
	_drawable->move(vector);
}

void Transform::moveTo(vec3 target)
{
	_drawable->move(target - _position);
	_position = target;
}

void Transform::rotateDeg(float angle, vec3 axis)
{
	_drawable->rotateDeg(angle, axis);
}

std::shared_ptr<DrawableObject> Transform::getDrawable() const
{
	return _drawable;
}

std::shared_ptr<Collider> Transform::getCollider() const
{
	return _collider;
}
