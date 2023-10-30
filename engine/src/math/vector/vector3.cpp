#include "../../../headers/math/vector/vector3.h"

Vector3::Vector3() : Vector3(0.f, 0.f, 0.f) {};

Vector3::Vector3(float val) : Vector3(val, val, val) {};

Vector3::Vector3(float* xyz) : Vector3(xyz[0], xyz[1], xyz[3]) {};

Vector3::Vector3(float x_, float y_, float z_) {
    x = x_; y = y_; z = z_;
};

float& Vector3::operator[](int index) {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw "Indexing of Vector3 is invalid";
    }
};

float Vector3::operator[](int index) const {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw "Indexing of Vector3 is invalid";
    }
};

Vector3& Vector3::add(const Vector3& vector) {
    return add(vector.x, vector.y, vector.z);
};

Vector3& Vector3::add(float x_, float y_, float z_) {
    x += x_; y += y_; z += z_;
    return *this;
};

Vector3& Vector3::subtract(const Vector3& vector) {
    return subtract(vector.x, vector.y, vector.z);
};

Vector3& Vector3::subtract(float x_, float y_, float z_) {
    x -= x_; y -= y_; z -= z_;
    return *this;
};

Vector3& Vector3::multiply(float scalar) {
    return multiply(scalar, scalar, scalar);
};

Vector3& Vector3::multiply(Vector3& vector) {
    return multiply(vector[0], vector[1], vector[2]);
};

Vector3& Vector3::multiply(float x_, float y_, float z_) {
    x *= x_; y *= y_; z *= z_;
    return *this;
};

Vector3& Vector3::copy(const Vector3& vector) {
    return set(vector.x, vector.y, vector.z);
};

Vector3& Vector3::set(float x_, float y_, float z_) {
    x = x_; y = y_; z = z_;
    return *this;
};

Vector3& Vector3::normalize() {
    float l = length();
    x /= l; y /= l; z /=l;
    return *this;
}

float Vector3::length() const { return length(x, y, z); };

float Vector3::length(float x, float y, float z) { return sqrt(x * x + y * y + z * z); };

float Vector3::distanceTo(const Vector3& v) { return Vector3::length(x - v.x, y - v.y, z - v.z); };

float Vector3::dot(const Vector3& v) { return dot(*this, v); };

float Vector3::dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
};

Vector3& Vector3::cross(const Vector3& v) { return cross(*this, v, &(*this)); };

Vector3& Vector3::cross(const Vector3& v1, const Vector3& v2, Vector3* out) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    out->set(x, y, z);
    return *out;
};

Vector3& Vector3::crossY() { y = x; x = -z; z = y; y = 0.0f; return *this; };

Vector3& Vector3::crossedByY() { y = x; x = z; z = -y; y = 0.0f; return *this; };