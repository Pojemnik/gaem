#include "resources.h"

const VertexArray& Resources::getVertexArray(std::string name)
{
	return (const VertexArray&)_verticesMap[name];
}

void Resources::addVertexArray(std::string name, std::string path)
{
	std::cout << "Loading model " << name << " from " << path << "..." << std::endl;
	_verticesMap.emplace(name, path);
	std::cout << "completed" << std::endl;
}

const Texture& Resources::getTexture(std::string name)
{
	return (const Texture&)_texturesMap[name];
}

void Resources::addTexture(std::string name, std::string path)
{
	std::cout << "Loading texture " << name << " from " << path << "..." << std::endl;
	_texturesMap.emplace(name, path);
	std::cout << "completed" << std::endl;
}
