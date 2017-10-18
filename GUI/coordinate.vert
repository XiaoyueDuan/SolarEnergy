#version 330 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
out vec3 Color;
uniform mat4 modelCoor;
uniform mat4 viewCoor;
uniform mat4 projectionCoor;
void main()
{
	Color = vColor;
	gl_Position = projectionCoor * viewCoor * modelCoor * vec4(vPosition, 1.0);
}