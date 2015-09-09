#version 410
out vec4 outputColor;

uniform sampler2D font;
uniform int text[11];

in vec2 inputPosition;

void main()
{

  float x = mod(inputPosition.x, 1.0);
  float y = inputPosition.y;


  int character = text[int(inputPosition.x)];
  vec2 inputCharacter = vec2(mod(character, 16), character / 16);

  vec2 charSize = vec2(1.0/16, 1.0/14);
  vec2 pos = vec2(x, -y);
  pos += inputCharacter;
  pos += vec2(0, 1);
  pos *= charSize;
  vec4 result = texture(font, pos);
  if (result.r < 0.1)
    discard;
  else
    outputColor = result;
}


