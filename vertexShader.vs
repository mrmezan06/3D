#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 color;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
// orderly manner 
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    color = vec4(aColor, 1.0f);
}
