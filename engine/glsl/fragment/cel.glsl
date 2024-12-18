#version 300 es
precision highp float;
out vec4 fragColor;

in vec3 vWorldNormal, vColor, vWorldPosition, vCameraWorldPosition;

// TO DO: The following are constants that should be passed as uniforms
// ====================
const float ambientI = 0.2;

const vec3 directional = -normalize(vec3(1.0, 1.0, 1.0));
const float directionalI = 0.7;

const vec3 point = vec3(1.0, 0.0, 0.0);
const float pointI = 0.8;

const int toonLevels = 5;
const float rimPower = 4.0;
// ====================

float computeLambert(vec3 normal, vec3 reversedLightDirection) {
    return max(0.0, dot(normal, reversedLightDirection));
}

float computeRimFactor(vec3 position, vec3 normal, vec3 cameraPosition) {
    vec3 reversedView = normalize(cameraPosition - position);
    float rimFactor = dot(normal, reversedView);
    if (rimFactor <= 0.0) return 0.0;
    rimFactor = pow(1.0 - rimFactor, rimPower);
    return rimFactor;
}

float computeLight(vec3 position, vec3 normal, vec3 cameraPosition, float intensity, vec3 reversedLightDirection) {
    float diffuse = computeLambert(normal, reversedLightDirection);
    return intensity * (computeRimFactor(position, normal, cameraPosition) + ceil(diffuse * float(toonLevels)) / float(toonLevels));
}

void main() {
    float directionalDynamicI = computeLight(vWorldPosition, vWorldNormal, vCameraWorldPosition, directionalI, -directional);
    float pointDynamicI = computeLight(vWorldPosition, vWorldNormal, vCameraWorldPosition, pointI, normalize(point- vWorldPosition));
    fragColor = vec4(vColor * (ambientI + directionalDynamicI + pointDynamicI), 1.0);
}