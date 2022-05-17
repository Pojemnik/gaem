#include "resources.h"

const VertexArray& Resources::getVertexArray(std::string name)
{
	return (const VertexArray&)_verticesMap[name];
}

void Resources::addVertexArray(std::string name, std::string path)
{
	_verticesMap.emplace(name, path);
}
