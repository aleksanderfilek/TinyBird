#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float texIndex;

uniform mat4 pixel;

out VS_OUT
{
  vec2 TexCoords;
  float TexIndex;
} vs_out;

void main()
{
  vs_out.TexCoords = texCoords;
  vs_out.TexIndex = texIndex;
  gl_Position = pixel * vec4(position, 0.0, 1.0);
}