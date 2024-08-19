#pragma once
#include <iostream>
#include <math.h>

#define M_PI 3.14159265358979323846
#define Radians(x) x * 0.01745329251994329576923690768489

struct Vector3 {
    float x, y, z;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vector3(float array[3]) : x(array[0]), y(array[1]), z(array[2]) {}
    Vector3(const Vector3& b) : x(b.x), y(b.y), z(b.z) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(const float& k) const { return Vector3(k * x, k * y, k * z); }
    friend Vector3 operator*(const float& k, const Vector3& m) { return Vector3(k * m.x, k * m.y, k * m.z); }

    float module() const { return sqrtf(x * x + y * y + z * z); }
    Vector3& normalize() {
        float mod = sqrtf(x * x + y * y + z * z);
        x /= mod;
        y /= mod;
        z /= mod;
        return *this;
    }
    
    Vector3 cross(const Vector3& b) const {
        return Vector3(
            y * b.z - z * b.y,
            z * b.x - x * b.z,
            x * b.y - y * b.x);
    }
    
    float dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
};
struct Vector4 {
    float x, y, z, w;
    Vector4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}
};

// Mat4采用列优先存储，以适应OpenGL需要
class Mat4
{
public:
    float val[4][4];
    Mat4(float i = 1);
    
    Mat4 operator*(Mat4& b);
    void translate(Vector3 v);
    void rotate(float angle, Vector3 u);
    void scale(Vector3 s);
};

Mat4 perspective(float fovy, float aspect, float zNear, float zFar);
Mat4 lookAtRH(const Vector3& eye, const Vector3& center, const Vector3& up);