#pragma once

#include <GL/freeglut.h>
#include "core/Object3D.hpp"
#include "core/Vector3.hpp"

namespace pgl {

class PlaneObject : public Object3D {
public:
    PlaneObject(double sizeX, double sizeY,
                double segmentsX = 1, double segmentsY = 1)
        : _sizeX(sizeX), _sizeY(sizeY), _segmentsX(segmentsX), _segmentsY(segmentsY) {}

protected:
    double _sizeX;
    double _sizeY;
    double _segmentsX;
    double _segmentsY;
};

} // namespace pgl
