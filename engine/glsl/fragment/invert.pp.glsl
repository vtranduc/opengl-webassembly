#version 300 es
precision highp float;

out vec4 fragColor;

uniform sampler2D screenTexture;

in vec2 vUv;

void main()
{
    fragColor = vec4(vec3(1.0 - texture(screenTexture, vUv)), 1.0);
}