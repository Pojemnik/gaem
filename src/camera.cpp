#include "camera.h"

Camera::Camera(vec3 position,float fov, float aspect, float near, float far,
	const Window& window, vec3 up) : _position(position), _fov(fov),
	_aspect(aspect), _near(near), _far(far), _up(up), _rotation(0, 0, -90)
{
	recalcViewAndPerspective();
	glm::ivec2 windowSize = window.getSize();
	_ortho = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f,
		static_cast<float>(windowSize.y));
}

void Camera::recalcViewAndPerspective()
{
	_view = glm::lookAt(_position, _direction + _position, _up);
	_perspective = glm::perspective(_fov, _aspect, _near, _far);
	_recalcNeeded = false;
}

void Camera::update()
{
	if (_recalcNeeded)
	{
		recalcViewAndPerspective();
	}
}

void Camera::move(vec3 delta)
{
	vec3 deltaInLocalSpace = delta.z * _direction + delta.y * vec3(0, 1, 0) +
		delta.x * glm::cross(_direction, vec3(0, 1, 0));
	_position += deltaInLocalSpace;
	_recalcNeeded = true;
}

void Camera::moveTo(vec3 target)
{
	_position = target;
	_recalcNeeded = true;
}

void Camera::set2DRotation(vec2 inputVector)
{
	_rotation.yaw += inputVector.x;
	_rotation.pitch += inputVector.y;

	if (_rotation.pitch > 89.0f)
		_rotation.pitch = 89.0f;
	if (_rotation.pitch < -89.0f)
		_rotation.pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(_rotation.yaw))
		* cos(glm::radians(_rotation.pitch));
	direction.y = sin(glm::radians(_rotation.pitch));
	direction.z = sin(glm::radians(_rotation.yaw))
		* cos(glm::radians(_rotation.pitch));
	_direction = glm::normalize(direction);
	_recalcNeeded = true;
}

mat4 Camera::getOrthoMatrix() const
{
	return _ortho;
}

mat4 Camera::getViewMatrix() const
{
	return _view;
}

mat4 Camera::getPerspectiveMatrix() const
{
	return _perspective;
}

Camera::CameraRotation::CameraRotation(float aRoll, float aPitch, float aYaw)
	: roll(aRoll), pitch(aPitch), yaw(aYaw) {}
