#include "drawableObject.h"

DrawableObject::DrawableObject(std::unique_ptr<Model> model)
	: _model(std::move(model)), _matrix(1.0f) {}

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

void DrawableObject::draw(const Shader& shader)
{
	shader.setUniformMatrix("M", _matrix);
	shader.enableAndSetAttributeArray("vertex", _model->getVertices(), 4);
	shader.enableAndSetAttributeArray("normal", _model->getNormals(), 3);
	glDrawArrays(GL_TRIANGLES, 0, _model->getVerticesSize());
	shader.disableAttributeArray("vertex");
	shader.disableAttributeArray("normal");
}
