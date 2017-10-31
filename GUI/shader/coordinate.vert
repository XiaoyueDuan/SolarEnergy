#version 330 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
out vec3 Color;
uniform mat4 model;

void main()
{
    Color = vColor;
    gl_Position = model* vec4(vPosition,1.0);
}