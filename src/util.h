#pragma once
#include <glm.hpp>
#include <iostream>

#include "definitions.h"

#define printOpenGLErrorIfAny() printOpenGLErrorIfAny_(__FILE__, __LINE__) 

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

inline void printOpenGLErrorIfAny_(const char* file, int line)
{
    GLenum error = glGetError();
    if (error != 0)
    {
        std::cout << "Error: " << file << " | " << line << std::endl;
        std::cout << error << std::endl;
    }
}