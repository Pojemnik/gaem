#include "shader.h"

const std::string Shader::readShaderFromFile(const std::string& path) const
{
	std::ifstream shaderFile(path);
	std::ostringstream vertexBuffer;
	vertexBuffer << shaderFile.rdbuf();
	return vertexBuffer.str();
}

GLuint Shader::loadShader(GLenum shaderType, const std::string& path) const
{
	GLuint handler;
	handler = glCreateShader(shaderType);
	const std::string source = readShaderFromFile(path);
	const GLchar* arr = source.c_str();
	glShaderSource(handler, 1, &arr, NULL);
	glCompileShader(handler);

	int success;
	std::string info;
	glGetShaderiv(handler, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(handler, 512, NULL, info.data());
		std::cout << "Shader compilation failed:\n" << info << std::endl;
	}
	return handler;
}

Shader::Shader(std::string fragmentPath, std::string geometryPath, std::string vertexPath)
{
	_shaderHandler = glCreateProgram();
	_fragmentHandler = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	_geometryHandler = loadShader(GL_GEOMETRY_SHADER, geometryPath);
	_vertexHandler = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(_shaderHandler, _fragmentHandler);
	glAttachShader(_shaderHandler, _geometryHandler);
	glAttachShader(_shaderHandler, _vertexHandler);
	glLinkProgram(_shaderHandler);
	getLinkingError();
}

Shader::Shader(std::string fragmentPath, std::string vertexPath)
{
	_shaderHandler = glCreateProgram();
	_fragmentHandler = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	_vertexHandler = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(_shaderHandler, _fragmentHandler);
	glAttachShader(_shaderHandler, _vertexHandler);
	glLinkProgram(_shaderHandler);
	getLinkingError();
}

void Shader::setUniformMatrix(const std::string& name, const glm::mat4& mat)
{
	const auto location = glGetUniformLocation(_shaderHandler, name.c_str());
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
}

void Shader::setAttributePointer(const std::string& name, const std::vector<float>& val)
{
}

void Shader::use()
{
	glUseProgram(_shaderHandler);
}

Shader::~Shader()
{
	glDetachShader(_shaderHandler, _vertexHandler);
	if (_geometryHandler != -1)
	{
		glDetachShader(_shaderHandler, _geometryHandler);
	}
	glDetachShader(_shaderHandler, _fragmentHandler);

	glDeleteShader(_vertexHandler);
	if (_geometryHandler != -1) 
	{
		glDeleteShader(_geometryHandler);
	}
	glDeleteShader(_fragmentHandler);

	glDeleteProgram(_shaderHandler);
}

void Shader::getLinkingError() const
{
	int success;
	std::string info;
	glGetShaderiv(_shaderHandler, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(_shaderHandler, 512, NULL, info.data());
		std::cout << "Shader linking failed:\n" << info << std::endl;
	}
}
