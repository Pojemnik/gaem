#include "shader.h"

const std::string Shader::readShaderFromFile(std::string path) const
{
	std::ifstream shaderFile(path);
	std::ostringstream vertexBuffer;
	vertexBuffer << shaderFile.rdbuf();
	return vertexBuffer.str();
}

GLuint Shader::loadShader(GLenum shaderType, std::string path) const
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
	shaderHandler = glCreateProgram();
	fragmentHandler = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	geometryHandler = loadShader(GL_GEOMETRY_SHADER, geometryPath);
	vertexHandler = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(shaderHandler, fragmentHandler);
	glAttachShader(shaderHandler, geometryHandler);
	glAttachShader(shaderHandler, vertexHandler);
	glLinkProgram(shaderHandler);
	getLinkingError();
}

Shader::Shader(std::string fragmentPath, std::string vertexPath)
{
	shaderHandler = glCreateProgram();
	fragmentHandler = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	vertexHandler = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(shaderHandler, fragmentHandler);
	glAttachShader(shaderHandler, vertexHandler);
	glLinkProgram(shaderHandler);
	getLinkingError();
}

Shader::~Shader()
{
	glDetachShader(shaderHandler, vertexHandler);
	if (geometryHandler != -1)
	{
		glDetachShader(shaderHandler, geometryHandler);
	}
	glDetachShader(shaderHandler, fragmentHandler);

	glDeleteShader(vertexHandler);
	if (geometryHandler != -1) 
	{
		glDeleteShader(geometryHandler);
	}
	glDeleteShader(fragmentHandler);

	glDeleteProgram(shaderHandler);
}

void Shader::getLinkingError() const
{
	int success;
	std::string info;
	glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderHandler, 512, NULL, info.data());
		std::cout << "Shader linking failed:\n" << info << std::endl;
	}
}
