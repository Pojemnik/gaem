#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <glm.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

class Model
{
public:
	struct Indices
	{
		std::vector<int> vertex;
		std::vector<int> normal;
		std::vector<int> tex;
	};

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normal;
	std::vector<glm::vec2> _texcoord;
	Indices _indices;


public:

	Model(std::string path);
};

