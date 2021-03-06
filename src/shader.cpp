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
	glGetShaderiv(handler, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::string info;
		char c[512];
		glGetShaderInfoLog(handler, 512, NULL, c);
		std::cout << "Shader compilation failed:\n" << c << std::endl;
	}
	return handler;
}

Shader::Shader(std::string fragmentPath, std::string geometryPath, std::string vertexPath)
{
	_shaderHandler = glCreateProgram();
	_fragmentHandler = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	_geometryHandler = loadShader(GL_GEOMETRY_SHADER, geometryPath);
	_vertexHandler = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(_shaderHandler, _vertexHandler);
	glAttachShader(_shaderHandler, _geometryHandler);
	glAttachShader(_shaderHandler, _fragmentHandler);
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

void Shader::setUniformMatrix(const std::string& name, const glm::mat4& mat) const
{
	const GLuint location = glGetUniformLocation(_shaderHandler, name.c_str());
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
}

void Shader::setUniform3f(const std::string& name, const vec3 val) const
{
	const GLuint location = glGetUniformLocation(_shaderHandler, name.c_str());
	glUniform3f(location, val.x, val.y, val.z);
}

void Shader::setUniform4f(const std::string& name, const vec4 val) const
{
	const GLuint location = glGetUniformLocation(_shaderHandler, name.c_str());
	glUniform4f(location, val.x, val.y, val.z, val.w);
}

void Shader::setUniform1i(const std::string& name, GLuint value) const
{
	const GLuint location = glGetUniformLocation(_shaderHandler, name.c_str());
	glUniform1i(location, value);
}

void Shader::enableAndSetAttributeArray(const std::string& name, const std::vector<float>& val, int size) const
{
	const GLuint location = glGetAttribLocation(_shaderHandler, name.c_str());
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, false, 0, val.data());
}

void Shader::disableAttributeArray(const std::string& name) const
{
	const GLuint location = glGetAttribLocation(_shaderHandler, name.c_str());
	glDisableVertexAttribArray(location);
}

void Shader::use() const
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
	glGetProgramiv(_shaderHandler, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_shaderHandler, 512, NULL, info.data());
		std::cout << "Shader linking failed:\n" << info << std::endl;
	}
}
