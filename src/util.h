#pragma once
#include <glm.hpp>
#include <iostream>

#include "definitions.h"

inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    os << "x: " << v.x << " y: " << v.y;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    os << "x: " << v.x << " y: " << v.y << " z: " << v.z;
    return os;
}