#version 330 core

out vec4 FragColor;

uniform sampler2D sb_textures[32];

in VS_OUT
{
  vec2 TexCoords;
  float TexIndex;
} fs_in;

void main()
{
  int index = int(fs_in.TexIndex);
  FragColor = texture(sb_textures[index], fs_in.TexCoords);
}
