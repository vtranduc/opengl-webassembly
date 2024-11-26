#version 300 es
precision highp float;

out vec4 fragColor;

uniform sampler2D screenTexture;

in vec2 vUv;

const int nRings = 7;
const int nPointsPerRing = 8;
const float effectDistance = 0.05;

const float distanceInterval = effectDistance / float(nRings);
const float angleInterval = 6.28318530718 / float(nPointsPerRing);

void main()
{
    vec3 acc = texture(screenTexture, vUv).xyz;
    for (int i = 1; i < nRings; i++) {
        float r = float(i) * distanceInterval;
        vec3 ringAcc = vec3(0.0);
        int nValidSamplingPoints = 0;
        for (int j = 0; j < nPointsPerRing; j++) {
            float angle = float(j) * angleInterval;
            vec2 uv = vec2(vUv.x + r * cos(angle), vUv.y + r * sin(angle));
            if (uv.x < 0.0 || uv.y < 0.0 || uv.x > 1.0 || uv.y > 1.0) continue;
            nValidSamplingPoints++;
            ringAcc += texture(screenTexture, uv).xyz;
        }
        acc += ringAcc / float(nValidSamplingPoints);
    }
    fragColor = vec4(acc / float(nRings), 1.0);
}