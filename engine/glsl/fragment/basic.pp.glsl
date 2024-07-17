#version 300 es
precision highp float;

out vec4 fragColor;

uniform sampler2D screenTexture;

in vec2 vUv;

void main()
{ 
    fragColor = texture(screenTexture, vUv);
}