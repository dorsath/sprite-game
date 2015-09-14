#version 410
out vec4 outputColor;

in vec2 vertexCoords;
uniform sampler2D sprite;
uniform int animation;
uniform bool mirror;
uniform int direction;
//uniform vec2 sprite;

void main() {
  vec2 nSprite = vec2(int(animation),int(direction));
  vec2 textureCoords;
  if (mirror){
    textureCoords = (nSprite + vertexCoords * vec2(-1, -1));
    textureCoords += vec2(1.0, 1.0);
  } else {
    textureCoords = (nSprite + vertexCoords * vec2(1, -1));
    textureCoords += vec2(0.0, 1.0);
  }
    

  vec2 spriteLayout = vec2(6.0, 10.0);
  textureCoords *= 1/spriteLayout;

  vec4 result = texture(sprite, textureCoords);
  if (result.w == 0)
    discard;
  else
    outputColor = result;

}


