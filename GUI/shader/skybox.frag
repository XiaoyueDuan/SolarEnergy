#version 330 core
in vec3 Texcoord;
uniform samplerCube skybox;
out vec4 fColor;
void main()
{
    fColor = texture(skybox,Texcoord);
}