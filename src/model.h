#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include <glm.hpp>

#include "definitions.h"

class Model
{
private:
	std::unordered_map<BufferType, std::vector<float>> _data;
	std::unordered_map<BufferType, int> _sizes;

public:
	Model(std::string path);
	const std::vector<float>& getVector(BufferType type) const;
	int getSize(BufferType type) const;
	int getLength(BufferType type) const;
};

