#pragma once

#include <math.h>

class Vector3 {

public:

    Vector3();

    Vector3(float val);

    Vector3(float* xyz);

    Vector3(float x, float y, float z);

    float& operator[] (int);

    Vector3& add(const Vector3& vector);

    Vector3& add(float x, float y, float z);

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

    float x, y, z;
};