#version 300 es
precision highp float;
out vec4 fragColor;

in vec3 vWorldNormal, vColor, vWorldPosition, vCameraWorldPosition;

// TO DO: The following are constants that should be passed as uniforms
// ====================
const float ambientI = 0.2;
const float shininess = 100.0;

const vec3 directional = -normalize(vec3(1.0, 1.0, 1.0));
const float directionalI = 0.7;

const vec3 point = vec3(1.0, 0.0, 0.0);
const float pointI = 0.8;
// ====================

float computeLambert(vec3 normal, vec3 reversedLightDirection) {
    return max(0.0, dot(normal, reversedLightDirection));
}

float computePhong(vec3 position, vec3 normal, vec3 cameraPosition, float shininess, vec3 reversedLightDirection) {
    vec3 R = normalize(2.0 * normal * dot(normal, reversedLightDirection) - reversedLightDirection);
    vec3 V = normalize(cameraPosition - position);
    float dotProduct = dot(R, V);
    return dotProduct <= 0.0 ? 0.0 : pow(dotProduct, shininess);
}

float computeLight(vec3 position, vec3 normal, vec3 cameraPosition, float intensity, float shininess, vec3 reversedLightDirection) {
    float diffuse = computeLambert(normal, reversedLightDirection);
    float specular = computePhong(position, normal, cameraPosition, shininess, reversedLightDirection);
    return intensity * (diffuse + specular);
}

void main() {
    float directionalDynamicI = computeLight(vWorldPosition, vWorldNormal, vCameraWorldPosition, directionalI, shininess, -directional);
    float pointDynamicI = computeLight(vWorldPosition, vWorldNormal, vCameraWorldPosition, pointI, shininess, normalize(point- vWorldPosition));
    fragColor = vec4(vColor * (ambientI + directionalDynamicI + pointDynamicI), 1.0);
}