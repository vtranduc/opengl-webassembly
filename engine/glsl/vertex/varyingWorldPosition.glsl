precision highp float;

attribute vec3 position;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

varying vec4 vWorldPosition;

void main() {
    vWorldPosition = world * vec4(position, 1.0);
    gl_Position = projection * view * vWorldPosition;
}