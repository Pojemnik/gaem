#include "vertexArray.h"

void VertexArray::bindBuffer(GLuint& buffer, int length,
	const std::vector<float>& data)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), data.data(),
		GL_STATIC_DRAW);
}

VertexArray::VertexArray(const std::string& filePath)
{
	Model model(filePath);
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);
	bindBuffer(_vertexBuffer, model.getVerticesSize(), model.getVertices());
	bindBuffer(_normalBuffer, model.getNormalsSize(), model.getNormals());
	glBindVertexArray(0);
}
