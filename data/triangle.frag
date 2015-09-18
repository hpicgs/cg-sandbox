#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) out vec3 out_color;

in vec3 color;

void main()
{
    out_color = color;
}
