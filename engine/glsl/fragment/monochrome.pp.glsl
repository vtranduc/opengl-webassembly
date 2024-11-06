#version 300 es
precision highp float;

out vec4 fragColor;

uniform sampler2D screenTexture;

in vec2 vUv;

void main()
{
    vec3 color = texture(screenTexture, vUv).xyz;
    float compAve = (color.x + color.y + color.z) / 3.0;
    fragColor = vec4(vec3(compAve), 1.0);
}