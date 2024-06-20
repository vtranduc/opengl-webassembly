precision highp float;

attribute vec3 position, normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

varying vec3 vNormal;

void main() {
    vNormal = normal;
    gl_Position = projection * view * world * vec4(position, 1.0);
}