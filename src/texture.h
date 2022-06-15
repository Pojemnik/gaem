#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lodepng.h>

#include <string>
#include <vector>
#include <iostream>

#include "definitions.h"

class Texture
{
private:
	GLuint _textureId = -1;

	void generate(const std::vector<unsigned char>& data, unsigned int width,
		unsigned int height);

public:
	Texture() = default;
	Texture(std::string filename);
	GLuint getTexture();
};

