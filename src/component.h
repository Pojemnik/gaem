#pragma once
#include <memory>

class Transform;

class Component
{
private:
	Transform& _transform;

public:
	Component(Transform& transform);
	Transform& getTransform() const;
};