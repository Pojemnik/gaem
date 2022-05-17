#include "drawableObject.h"

DrawableObject::DrawableObject(const VertexArray& vertexArray)
	: _vertexArray(vertexArray), _matrix(1.0f) {}

void DrawableObject::rotate(float angle, vec3 axis)
{
	_matrix = glm::rotate(_matrix, angle, axis);
}

void DrawableObject::rotateDeg(float angle, vec3 axis)
{
	_matrix = glm::rotate(_matrix, glm::radians(angle), axis);
}

void DrawableObject::move(vec3 direction)
{
	_matrix = glm::translate(_matrix, direction);
}

void DrawableObject::scale(vec3 coef)
{
	_matrix = glm::scale(_matrix, coef);
}

void DrawableObject::draw(const Camera& camera, const Shader& shader)
{
	shader.use();
	shader.setUniformMatrix("M", _matrix);
	shader.setUniformMatrix("P", camera.getPerspectiveMatrix());
	shader.setUniformMatrix("V", camera.getViewMatrix());
	glBindVertexArray(_vertexArray.getArray());
	glDrawArrays(GL_TRIANGLES, 0, _vertexArray.getSize());
	glBindVertexArray(0);
}
