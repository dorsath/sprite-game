#version 410
out vec4 outputColor;

in vec2 vertexCoords;
uniform sampler2D sprites;
uniform vec2 sprite;

void main() {
  vec2 textureCoords = (sprite + vertexCoords * vec2(1, -1));
  textureCoords += vec2(0, 1);
  textureCoords *= vec2(1.0/64.0, 1.0/48.0);
  vec4 result = texture(sprites, textureCoords);
  if (result.w == 0)
    discard;
  else
    outputColor = result;

}


