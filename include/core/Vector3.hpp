#pragma once

#include <stdio.h>

namespace pgl {

class Vector3 {
public:
    static double Dot(const Vector3 &lhs, const Vector3 &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs) {
        Vector3 out;
        out.x = lhs.y * rhs.z - lhs.z * rhs.y;
        out.y = lhs.z * rhs.x - lhs.x * rhs.z;
        out.z = lhs.x * rhs.y - lhs.y * rhs.x;
        return out;
    }
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3(const Vector3 &rhs) {
        if (this == &rhs) {
            return;
        }
        *this = rhs;
    }

    Vector3 &operator=(const Vector3 &rhs) {
        if (this == &rhs) {
            return *this;
        }
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    const Vector3 operator+(const Vector3 &rhs) const {
        return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }
    const Vector3 operator-(const Vector3 &rhs) const {
        return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    }

    void Set(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Dump() {
        printf("[ %5.2f %5.2f %5.2f ]\n", x, y, z);
    }

    double x;
    double y;
    double z;
};

} // namespace pgl
