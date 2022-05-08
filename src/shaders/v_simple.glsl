#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 normal;


void main(void)
{
    gl_Position = P * V * M * vertex;
}
