precision highp float;

varying vec3 vVertexColor;

void main() {
    gl_FragColor = vec4(vVertexColor, 1.0);
}