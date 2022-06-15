#pragma once
#include <memory>

#include "definitions.h"
#include "drawableObject.h"
#include "collider.h"

class Transform : public Component
{
private:
	vec3 _position;
	std::shared_ptr<DrawableObject> _drawable;
	std::shared_ptr<Collider> _collider;

public:
	Transform(vec3 position, std::shared_ptr<DrawableObject> drawable, std::shared_ptr<Collider> collider = nullptr);
	void moveRelative(vec3 vector);
	void moveTo(vec3 position);
	void rotateDeg(float angle, vec3 axis);
	std::shared_ptr<DrawableObject> getDrawable() const;
	std::shared_ptr<Collider> getCollider() const;
};

