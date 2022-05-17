#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

#include "model.h"
#include "definitions.h"

class VertexArray
{
private:
	GLuint _vertexArray;
	GLuint _vertexBuffer;
	GLuint _colorBuffer;
	GLuint _texCoordBuffer;
	GLuint _normalBuffer;
	int _size;
	void bindBuffer(GLuint& buffer, int length, const std::vector<float>& data,
		BufferType type, int size);

public:
	VertexArray() = default;
	VertexArray(const std::string& filePath);
	virtual ~VertexArray();
	int getSize() const;
	GLuint getArray() const;
};

