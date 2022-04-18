#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
private:
	GLuint _shaderHandler;
	GLuint _fragmentHandler;
	GLuint _geometryHandler = -1;
	GLuint _vertexHandler;

	void getLinkingError() const;
	const std::string readShaderFromFile(std::string path) const;
	GLuint loadShader(GLenum shaderType, std::string path) const;

public:
	Shader(std::string fragmentPath, std::string geometryPath, std::string vertexPath);
	Shader(std::string fragmentPath, std::string vertexPath);
	~Shader();
};