#version 410
out vec4 outputColor;
smooth in vec4 theColor;

void main()
{

  outputColor = mix(
      vec4(0.0, 0.0, 0.0, 1.0),
      vec4(0.6, 0.6, 0.6, 1.0),
      theColor.z);
}

