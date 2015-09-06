#version 410
out vec4 outputColor;
smooth in vec4 theColor;
in vec4 vertexPoint;

void main()
{
  outputColor = theColor;
}
