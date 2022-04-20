#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

class Shader
{
private:
	GLuint _shaderHandler;
	GLuint _fragmentHandler;
	GLuint _geometryHandler = -1;
	GLuint _vertexHandler;

	void getLinkingError() const;
	const std::string readShaderFromFile(const std::string& path) const;
	GLuint loadShader(GLenum shaderType, const std::string& path) const;

public:
	Shader(std::string fragmentPath, std::string geometryPath, std::string vertexPath);
	Shader(std::string fragmentPath, std::string vertexPath);
	void setUniformMatrix(const std::string& name, const glm::mat4& mat);
	void enableAndSetAttributeArray(const std::string& name, const std::vector<float>& val, int size);
	void disableAttributeArray(const std::string& name);
	void use();
	~Shader();
};