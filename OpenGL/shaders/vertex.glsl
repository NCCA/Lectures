#version 300 es
precision highp float;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec3 position;
in vec3 normal;
in vec2 uv;
out vec2 outUV;
out vec3 fragmentNormal;

void main()
{
  fragmentNormal = (normalMatrix*normal);
  outUV=uv;
  gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}
