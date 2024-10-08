precision highp float;

attribute vec3 position;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * world * vec4(position, 1.0);
}