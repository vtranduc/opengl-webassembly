#version 300 es
precision highp float;

in vec3 position, normal, color;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec3 vNormal, vColor, vWorldPosition, vCameraWorldPosition;

void main() {
    // TO DO: convert local normal to global normal
    vNormal = normal;
    vColor = color;
    mat4 invView = inverse(view);
    vCameraWorldPosition = invView[3].xyz / invView[3][3];
    vec4 worldPosition = world * vec4(position, 1.0);
    vWorldPosition = worldPosition.xyz / worldPosition.w;
    gl_Position = projection * view * worldPosition;
}