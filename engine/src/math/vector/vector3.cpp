#include "../../../headers/math/vector/vector3.h"

Vector3::Vector3() : Vector3(0.f, 0.f, 0.f) {};

Vector3::Vector3(float val) : Vector3(val, val, val) {};

Vector3::Vector3(float* xyz) : Vector3(xyz[0], xyz[1], xyz[3]) {};

Vector3::Vector3(float x_, float y_, float z_) {
    x = x_; y = y_; z = z_;
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

Vector3& Vector3::copy(const Vector3& vector) {
    return set(vector.x, vector.y, vector.z);
};

Vector3& Vector3::set(float x_, float y_, float z_) {
    x = x_; y = y_; z = z_;
    return *this;
};
