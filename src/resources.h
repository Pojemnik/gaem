#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

#include "vertexArray.h"
class Resources
{
private:
	inline static std::unordered_map<std::string, VertexArray> _verticesMap = 
		std::unordered_map<std::string, VertexArray>();

public:
	static const VertexArray& getVertexArray(std::string name);
	static void addVertexArray(std::string name, std::string path);
};

