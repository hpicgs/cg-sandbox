#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) in vec2 in_vertex;
layout (location = 1) in vec2 in_textureCoordinate;

out vec3 color;

void main()
{
    gl_Position = vec4(in_vertex, 0.0, 1.0);
    color = vec3(in_textureCoordinate, 0.0);
}
