#include "component.h"

Component::Component(Transform& transform) : _transform(transform)
{
}

Transform& Component::getTransform() const
{
	return _transform;
}
