#pragma once
#include <memory>

#include "definitions.h"
#include "drawableObject.h"
#include "collider.h"

class Transform
{
private:
	vec3 _position;
	std::shared_ptr<DrawableObject> _drawableObject = nullptr;
	std::shared_ptr<Collider> _collider = nullptr;

public:
	Transform(vec3 position);
	void createDrawableObject(const VertexArray& vertexArray);
	void createCollider(vec3 halfExtend, vec3 position);
	void moveRelative(vec3 vector);
	void moveTo(vec3 position);
	void rotateDeg(float angle, vec3 axis);
	std::shared_ptr<Drawable> getDrawable() const;
	std::shared_ptr<DrawableObject> getDrawableObject() const;
	std::shared_ptr<Collider> getCollider() const;
	vec3 getPosition() const;
};

