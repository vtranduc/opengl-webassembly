#version 300 es
precision highp float;

in vec3 position, normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 uColor;

out vec3 vWorldNormal, vColor, vWorldPosition, vCameraWorldPosition;

void main() {
    vWorldNormal = normalize((transpose(inverse(world)) * vec4(normal, 0.0)).xyz);
    vColor = uColor;
    mat4 invView = inverse(view);
    vCameraWorldPosition = invView[3].xyz / invView[3][3];
    vec4 worldPosition = world * vec4(position, 1.0);
    vWorldPosition = worldPosition.xyz / worldPosition.w;
    gl_Position = projection * view * worldPosition;
}