#include "vertexArray.h"

void VertexArray::bindBuffer(GLuint& buffer, int length,
	const std::vector<float>& data, BufferType type, int size = 3)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), data.data(),
		GL_STATIC_DRAW);
	glVertexAttribPointer(static_cast<int>(type), size, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(static_cast<int>(type));
}

VertexArray::VertexArray(const std::string& filePath)
{
	Model model(filePath);
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);
	bindBuffer(_vertexBuffer, model.getLength(BufferType::VERTEX),
		model.getVector(BufferType::VERTEX), BufferType::VERTEX,
		model.getSize(BufferType::VERTEX));
	bindBuffer(_normalBuffer, model.getLength(BufferType::NORMAL),
		model.getVector(BufferType::NORMAL), BufferType::NORMAL,
		model.getSize(BufferType::NORMAL));
	bindBuffer(_texCoordBuffer, model.getLength(BufferType::TEXCOORD),
		model.getVector(BufferType::TEXCOORD), BufferType::TEXCOORD,
		model.getSize(BufferType::TEXCOORD));
	_size = model.getLength(BufferType::NORMAL);
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	//TODO
}

int VertexArray::getSize() const
{
	return _size;
}

GLuint VertexArray::getArray() const
{
	return _vertexArray;
}
