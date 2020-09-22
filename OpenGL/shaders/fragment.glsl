#version 300 es
precision highp float;

in vec3 fragmentNormal;
in vec2 outUV;

layout (location =0) out vec4 fragColour;
uniform vec4 colour1;
uniform vec4 colour2;

uniform vec3 lightPos;
uniform vec4 lightDiffuse;
uniform float checkSize;
uniform int checkOn;

vec4 checker( vec2 uv )
{
  if(checkOn == 0)
    return colour1;
  else
  {
  float v = floor( checkSize * uv.x ) +floor( checkSize * uv.y );
  if( mod( v, 2.0 ) < 1.0 )
     return colour2;
  else
     return colour1;

  }
}

void main ()
{
  fragColour= vec4(0.);
  vec3 N = normalize(fragmentNormal);
  vec3 L = normalize(lightPos);
  fragColour += checker(outUV)*lightDiffuse *dot(L, N);
}
