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

#include "definitions.h"
#include "util.h"

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
	void setUniformMatrix(const std::string& name, const mat4& mat) const;
	void setUniform3f(const std::string& name, const vec3 val) const;
	void setUniform4f(const std::string& name, const vec4 val) const;
	void setUniform1i(const std::string& name, GLuint value) const;
	void enableAndSetAttributeArray(const std::string& name, const std::vector<float>& val, int size) const;
	void disableAttributeArray(const std::string& name) const;
	void use() const;
	~Shader();
};