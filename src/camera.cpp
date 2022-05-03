#include "camera.h"

void Camera::recalc()
{
	_view = glm::lookAt(_position, _target, _up);
	_recalcNeeded = false;
	_perspective = glm::perspective(_fov, _aspect, _near, _far);
}

Camera::Camera(vec3 position, vec3 target, float fov, float aspect, float near, float far, vec3 up) :
	_position(position), _target(target), _fov(fov), _aspect(aspect), _near(near), _far(far), _up(up)
{
	recalc();
}

void Camera::update(const Shader& shader)
{
	if (_recalcNeeded)
	{
		recalc();
	}
	shader.setUniformMatrix("P", _perspective);
	shader.setUniformMatrix("V", _view);
}

void Camera::moveWithTarget(vec3 delta)
{
	_position += delta;
	_target += delta;
	_recalcNeeded = true;
}
