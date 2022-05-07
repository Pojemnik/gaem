#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <glm.hpp>

class Model
{
private:
	std::vector<float> _vertices;
	std::vector<float> _normals;
	std::vector<float> _texcoords;
	int _verticesSize;
	int _normalsSize;
	int _texcoordsSize;

public:
	Model(std::string path);
	const std::vector<float>& getVertices() const;
	const std::vector<float>& getNormals() const;
	const int getVerticesSize() const;
	const int getNormalsSize() const;
	const int getTexCoordsSize() const;
};

