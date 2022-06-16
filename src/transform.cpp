#include "transform.h"

Transform::Transform(vec3 position)
	: _position(position)
{
}

void Transform::createDrawableObject(const VertexArray& vertexArray)
{
	_drawableObject = std::make_shared<DrawableObject>(vertexArray);
	_drawableObject->move(_position);
}

void Transform::createCollider(vec3 halfExtend, vec3 position)
{
	_collider = std::make_shared<Collider>(halfExtend, position);
}

void Transform::moveRelative(vec3 vector)
{
	_position += vector;
	if (_drawableObject != nullptr)
	{
		_drawableObject->move(vector);
	}
}

void Transform::moveTo(vec3 target)
{
	if (_drawableObject != nullptr)
	{
		_drawableObject->move(target - _position);
	}
	_position = target;
}

void Transform::rotateDeg(float angle, vec3 axis)
{
	if (_drawableObject != nullptr)
	{
		_drawableObject->rotateDeg(angle, axis);
	}
}

std::shared_ptr<Drawable> Transform::getDrawable() const
{
	return _drawableObject;
}

std::shared_ptr<DrawableObject> Transform::getDrawableObject() const
{
	return _drawableObject;
}

std::shared_ptr<Collider> Transform::getCollider() const
{
	return _collider;
}

vec3 Transform::getPosition() const
{
	return _position;
}
