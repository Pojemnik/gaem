#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "ft2build.h"
#include FT_FREETYPE_H

#include "definitions.h"
#include "shader.h"
#include "util.h"

class Text
{
private:
	struct CharacterData
	{
		unsigned int textureId;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};
	std::unordered_map<char, CharacterData> _charactersData;
	GLuint _VAO, _VBO;
	vec2 _position = vec2(0, 0);
	vec3 _color = vec3(1, 1, 1);
	float _scale = 1;
	std::string _text;

	void generateVertexArray();

public:
	Text();
	void init(const Shader& shader);
	void draw(const Shader& shader);
	void setPosition(vec2 position);
	void setText(const std::string& text);
};

