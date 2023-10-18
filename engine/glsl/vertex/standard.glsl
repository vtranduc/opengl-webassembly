precision highp float;

attribute vec3 position;

uniform mat4 world;

void main() {
    gl_Position = world * vec4(position, 1.0);
}