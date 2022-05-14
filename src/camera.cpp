#include "camera.h"

Camera::Camera(vec3 position,float fov, float aspect, float near, float far,
	vec3 up) : _position(position), _fov(fov), _aspect(aspect), _near(near),
	_far(far), _up(up), _rotation(0, 0, -90)
{
	recalc();
}

void Camera::recalc()
{
	_view = glm::lookAt(_position, _direction + _position, _up);
	_perspective = glm::perspective(_fov, _aspect, _near, _far);
	_recalcNeeded = false;
}

void Camera::update(const Shader& shader)
{
	if (_recalcNeeded)
	{
		recalc();
	}
	shader.use();
	shader.setUniformMatrix("P", _perspective);
	shader.setUniformMatrix("V", _view);
}

void Camera::move(vec3 delta)
{
	_position += delta;
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

Camera::CameraRotation::CameraRotation(float aRoll, float aPitch, float aYaw)
	: roll(aRoll), pitch(aPitch), yaw(aYaw) {}
