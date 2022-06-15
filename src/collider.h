#pragma once
#include <memory>

#include "definitions.h"
#include "component.h"

class Collider : public Component
{
private:
	vec3 _halfExtend;

public:
	Collider(vec3 halfExtend, Transform& transform);
	vec3 getHalfExtend() const;
};

