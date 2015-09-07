#version 410
out vec4 outputColor;

uniform sampler2D font;

in vec2 inputPosition;
in vec2 inputCharacter;

void main()
{
  float x = mod(inputPosition.x, 1.0);
  float y = inputPosition.y;

  vec2 charSize = vec2(1.0/16, 1.0/14);
  vec2 pos = vec2(x, -y);
  pos += inputCharacter;
  pos += vec2(0, 1);
  pos *= charSize;
  outputColor = texture(font, pos);
}


