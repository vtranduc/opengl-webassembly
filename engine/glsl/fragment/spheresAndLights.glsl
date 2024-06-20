precision highp float;

varying vec3 vNormal;

void main() {
    float g = max(dot(vNormal, vec3(1.0, 0.0, 0.0)), 0.0);

    gl_FragColor = vec4(1.0, g, 0.0, 1.0);
}