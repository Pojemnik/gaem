#pragma once
#include <glm.hpp>
#include <rotate_vector.hpp>

#include "definitions.h"
#include "shader.h"
#include "window.h"

class Camera
{
private:
	struct CameraRotation
	{
		CameraRotation(float aRoll, float aPitch, float aYaw);
		float roll;
		float pitch;
		float yaw;
	};

	mat4 _view;
	mat4 _perspective;
	mat4 _ortho;

	CameraRotation _rotation;
	vec3 _direction = vec3(0, 0, 0);
	vec3 _position;
	vec3 _up;
	float _fov;
	float _aspect;
	float _near;
	float _far;

	bool _recalcNeeded = false;

	void recalcViewAndPerspective();

public:
	Camera(vec3 position, float fov, float aspect, float near, float far,
		const Window& window, vec3 up = vec3(0, 1, 0));
	void update();
	void move(vec3 delta);
	void moveTo(vec3 target);
	void set2DRotation(vec2 inputVector);
	mat4 getOrthoMatrix() const;
	mat4 getViewMatrix() const;
	mat4 getPerspectiveMatrix() const;
};

