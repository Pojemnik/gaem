#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

#include "vertexArray.h"
#include "texture.h"

class Resources
{
private:
	inline static std::unordered_map<std::string, VertexArray> _verticesMap = 
		std::unordered_map<std::string, VertexArray>();
	inline static std::unordered_map<std::string, Texture> _texturesMap =
		std::unordered_map<std::string, Texture>();

public:
	static const VertexArray& getVertexArray(std::string name);
	static void addVertexArray(std::string name, std::string path);

	static const Texture& getTexture(std::string name);
	static void addTexture(std::string name, std::string path);
};

