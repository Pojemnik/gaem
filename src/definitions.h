#pragma once
#include <glm.hpp>

typedef glm::vec3 vec3;
typedef glm::mat4 mat4;
typedef glm::vec2 vec2;

enum class BufferType : int
{
	VERTEX = 0,
	NORMAL,
	TEXCOORD,
	COLOR,
	TANGENT,
	BITANGENT
};