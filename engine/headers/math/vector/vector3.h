#pragma once

#include <math.h>
#include "../constants.h"

class Vector3 {

public:

    Vector3();

    Vector3(float val);

    Vector3(float* xyz);

    Vector3(float x, float y, float z);

    float& operator[] (int);

    float operator[] (int) const;

    Vector3& add(const Vector3& vector);

    Vector3& add(float x, float y, float z);

    Vector3& addX(float delta);

    Vector3& addY(float delta);

    Vector3& addZ(float delta);

    Vector3& subtract(const Vector3& vector);

    Vector3& subtract(float x, float y, float z);

    Vector3& multiply(float scalar);

    Vector3& multiply(Vector3& vector);

    Vector3& multiply(float x, float y, float z);

    Vector3& copy(const Vector3& vector);

    Vector3& set(float x, float y, float z);

    Vector3& normalize();

    float length() const;

    static float length(float x, float y, float z);

    float distanceTo(const Vector3& v);

    float dot(const Vector3& v);

    static float dot(const Vector3& v1, const Vector3& v2);

    Vector3& cross(const Vector3& v);

    static Vector3& cross(const Vector3& v1, const Vector3& v2, Vector3* out = new Vector3());

    Vector3& crossY();

    Vector3& crossedByY();

    Vector3& sphericalToCartesian();

    static Vector3& sphericalToCartesian(float r, float theta, float phi, Vector3* out = new Vector3());

    Vector3& sphericalToCartesianYUpConvention();

    static Vector3& sphericalToCartesianYUpConvention(float r, float theta, float phi, Vector3* out = new Vector3());

    Vector3& cartesianToSpherical();

    static Vector3& cartesianToSpherical(float x, float y, float z, Vector3* out = new Vector3());

    Vector3& cartesianToSphericalYUpConvention();

    static Vector3& cartesianToSphericalYUpConvention(float x, float y, float z, Vector3* out = new Vector3());

    float x, y, z;
};