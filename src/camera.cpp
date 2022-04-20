#include "camera.h"

void Camera::recalcView()
{
	_view = glm::lookAt(_position, _target, _up);
	_viewRecalcNeeded = false;
}

void Camera::recalcPerspective()
{
	_perspective = glm::perspective(_fov, _aspect, _near, _far);
	_perspectiveRecalcNeeded = false;
}

Camera::Camera(vec3 position, vec3 target, float fov, float aspect, float near, float far, vec3 up) :
	_position(position), _target(target), _fov(fov), _aspect(aspect), _near(near), _far(far), _up(up)
{
	recalcPerspective();
	recalcView();
}

void Camera::update(const Shader& shader)
{
	if (_viewRecalcNeeded)
	{
		recalcView();
	}
	if (_perspectiveRecalcNeeded)
	{
		recalcPerspective();
	}
	shader.setUniformMatrix("P", _perspective);
	shader.setUniformMatrix("V", _view);
}
