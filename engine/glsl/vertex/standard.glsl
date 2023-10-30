precision highp float;

attribute vec3 position;

uniform mat4 world;
uniform mat4 view;

void main() {
    gl_Position = view * world * vec4(position, 1.0);
}