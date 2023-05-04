#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform int nx = 1;
uniform int ny = 1;
uniform int frameIndex = 0;
uniform mat4 model;
uniform mat4 projection; 

out vec3 ourColor;
out vec2 TexCoord;

void main() 
{
    gl_Position = projection * model * vec4(position, 1.0f);
    ourColor = color;
    int frameX = frameIndex % nx;
    int frameY = frameIndex / nx;
    float x = ((1.0f / nx) * (texCoord.x + frameX));
    float y = ((1.0f / ny) * (texCoord.y + frameY)); 
    TexCoord = vec2(x, y);
}



