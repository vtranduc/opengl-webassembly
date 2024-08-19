precision highp float;

attribute vec3 position, normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

uniform float uDistance;

void main() {
    gl_Position = projection * view * world * vec4(position + normal * uDistance, 1.0);
}