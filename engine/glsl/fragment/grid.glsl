precision highp float;

uniform vec3 uColorOrigin, uColorX, uColorZ, uColorMajor, uColorMinor;

varying vec4 vWorldPosition;

const float marjorHalfWidthRatio = 0.06;

const float minorHalfWidthRatio = 0.05;

const float major = 0.1;

const int nMinor = 2;

const float originRadius = 0.06;

const float originInnerRadius = 0.03;

const float xzHalfWidth = 0.02;

bool getGridComponent(in float component, in float spacing, in float halfWidthRatio, out float alpha) {
    float distancePercentage = fract(component / spacing);
    if (distancePercentage < halfWidthRatio) {
        alpha = smoothstep(halfWidthRatio, 0.0, distancePercentage);
        return true;
    }
    float lowerLimit = 1.0 - halfWidthRatio;
    if (distancePercentage > lowerLimit) {
        alpha = smoothstep(lowerLimit, 1.0, distancePercentage);
        return true;
    }
    return false;
}

bool getGrid(vec2 xz, in float spacing, in float halfWidthRatio, out float alpha) {
    float xAlpha, zAlpha;
    bool isXGrid = getGridComponent(xz.x, spacing, halfWidthRatio, xAlpha);
    bool isZGrid = getGridComponent(xz.y, spacing, halfWidthRatio, zAlpha);
    if (isXGrid) {
        if (isZGrid) alpha = min(xAlpha + zAlpha, 1.0);
        else alpha = xAlpha;
        return true;
    } else if (isZGrid) {
        alpha = zAlpha;
        return true;
    } else return false;
}

void main() {
    vec2 xz = vWorldPosition.xz / vWorldPosition.w;

    // Origin
    float xzLen = length(xz);
    if (xzLen <= originRadius) {
        if (xzLen <= originInnerRadius) discard;
        else gl_FragColor = vec4(uColorOrigin, 1.0);
        return;
    }

    // xz axes
    float xAbs = abs(xz.x);
    if (xAbs < xzHalfWidth) {
        gl_FragColor = vec4(uColorX, smoothstep(xzHalfWidth, 0.0, xAbs));
        return;
    } else {
        float zAbs = abs(xz.y);
        if (zAbs < xzHalfWidth) {
            gl_FragColor = vec4(uColorZ, smoothstep(xzHalfWidth, 0.0, zAbs));
            return;
        }
    }

    // Grid
    float alpha;
    if (getGrid(xz, major, marjorHalfWidthRatio, alpha)) gl_FragColor = vec4(uColorMajor, alpha);
    else if (getGrid(xz, major / float(nMinor), minorHalfWidthRatio, alpha)) gl_FragColor = vec4(uColorMinor, alpha);
    else discard;
}