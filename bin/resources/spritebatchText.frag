#version 330 core

out vec4 FragColor;
uniform vec3 TextColor;
uniform sampler2D sb_textures[32];

in VS_OUT
{
  vec2 TexCoords;
  float TexIndex;
} fs_in;

void main()
{
  int index = int(fs_in.TexIndex);
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(sb_textures[index].r, fs_in.TexCoords));
  FragColor = vec4(TextColor, 1.0) * sampled;
}
