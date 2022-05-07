#pragma once
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <vector>
#include <string>

#include "model.h"

class VertexArray
{
private:
	GLuint _vertexArray;
	GLuint _vertexBuffer;
	GLuint _colorBuffer;
	GLuint _texCoordBuffer;
	GLuint _normalBuffer;

	void bindBuffer(GLuint& buffer, int length, const std::vector<float>& data);

public:
	VertexArray(const std::string& filePath);
};

