#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <glm.hpp>

class Model
{
private:
	std::vector<float> _vertices;
	std::vector<float> _normal;
	std::vector<float> _texcoord;
	int _size;

public:
	Model(std::string path);
	const std::vector<float>& getVertices() const;
	const std::vector<float>& getNormals() const;
	const int getSize() const;
};

