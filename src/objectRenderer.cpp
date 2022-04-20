#include "objectRenderer.h"

const float ObjectRenderer::_deg2rad = 3.1415f / 180;

ObjectRenderer::ObjectRenderer(std::unique_ptr<Model> model) : _model(std::move(model)), _matrix(1.0f) {}

void ObjectRenderer::rotate(float angle, vec3 axis)
{
	_matrix = glm::rotate(_matrix, angle, axis);
}

void ObjectRenderer::rotateDeg(float angle, vec3 axis)
{
	_matrix = glm::rotate(_matrix, angle * _deg2rad, axis);
}

void ObjectRenderer::move(vec3 direction)
{
	_matrix = glm::translate(_matrix, direction);
}

void ObjectRenderer::scale(vec3 coef)
{
	_matrix = glm::scale(_matrix, coef);
}

void ObjectRenderer::draw(const Shader& shader)
{
	shader.setUniformMatrix("M", _matrix);
	shader.enableAndSetAttributeArray("vertex", _model->getVertices(), 4);
	shader.enableAndSetAttributeArray("normal", _model->getNormals(), 3);
	glDrawArrays(GL_TRIANGLES, 0, _model->getSize());
	shader.disableAttributeArray("vertex");
	shader.disableAttributeArray("normal");
}
