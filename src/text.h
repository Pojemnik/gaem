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
	class GlyphDatabase
	{
	public:
		struct CharacterData
		{
			unsigned int textureId;
			glm::ivec2 size;
			glm::ivec2 bearing;
			unsigned int advance;
		};

	private:
		inline static bool _initialized = false;
		inline static std::unordered_map<char, CharacterData> _data;

		inline static void init();

	public:
		static CharacterData getGlyph(char character);
	};
	
	inline static GLuint _VAO;
	inline static GLuint _VBO;
	inline static bool _vertexArrayInitalized = false;

	vec2 _position = vec2(0, 0);
	vec3 _color = vec3(1, 1, 1);
	float _scale = 1;
	std::string _text;

	static void initializeVertexArray();

public:
	Text();
	void draw(const Shader& shader);
	void setPosition(vec2 position);
	void setText(const std::string& text);
};

