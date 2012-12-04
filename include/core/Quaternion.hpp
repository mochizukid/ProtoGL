#pragma once

#include <math.h>
#include <assert.h>

#include "core/Vector3.hpp"

namespace pgl {

class Quaternion {
public:
    static void RotatePoint(const Vector3 &src, double radian, const Vector3 &axis, Vector3 &dst) {
        Quaternion p(src.x, src.y, src.z);
        Quaternion q(radian, axis.x, axis.y, axis.z);
        Quaternion r(-radian, axis.x, axis.y, axis.z);

        Quaternion out = r * p * q;
        dst.Set(out.x, out.y, out.z);
    }
    
    Quaternion() : t(0.0), x(0.0), y(0.0), z(0.0) {}

    Quaternion(double x, double y, double z) {
        this->t = 0.0;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    Quaternion(double radian, double axisX, double axisY, double axisZ) {
        double norm;
        double c, s;
        
        norm = axisX * axisX + axisY * axisY + axisZ * axisZ;
        assert(norm != 0);
        
        norm = 1.0 / sqrt(norm);
        axisX *= norm;
        axisY *= norm;
        axisZ *= norm;
        
        c = cos(0.5 * radian);
        s = sin(0.5 * radian);
        
        this->t = c;
        this->x = s * axisX;
        this->y = s * axisY;
        this->z = s * axisZ;
    }

    Quaternion &operator=(const Quaternion &rhs) {
	if (this == &rhs) {
	    return *this;
	}
        *this = rhs;
        return (*this);
    }

    const Quaternion operator*(const Quaternion &rhs) const {
        Quaternion out;
        double d1, d2, d3, d4;

        d1 =  t * rhs.t;
        d2 = -x * rhs.x;
        d3 = -y * rhs.y;
        d4 = -z * rhs.z;
        out.t = d1 + d2 + d3 + d4;

        d1 =  t * rhs.x;
        d2 =  rhs.t * x;
        d3 =  y * rhs.z;
        d4 = -z * rhs.y;
        out.x = d1 + d2 + d3 + d4;

        d1 =  t * rhs.y;
        d2 =  rhs.t * y;
        d3 =  z * rhs.x;
        d4 = -x * rhs.z;
        out.y = d1 + d2 + d3 + d4;

        d1 =  t * rhs.z;
        d2 =  rhs.t * z;
        d3 =  x * rhs.y;
        d4 = -y * rhs.x;
        out.z = d1 + d2 + d3 + d4;

        return out;
    }

    double t;
    double x;
    double y;
    double z;
};

} // namespace pgl
