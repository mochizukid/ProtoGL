#pragma once

#include <GL/freeglut.h>
#include "core/Object3D.hpp"
#include "core/Vector3.hpp"

namespace pgl {

class GridObject : public Object3D {
public:
    GridObject(double sizeX, double sizeZ, double segmentsX, double segmentsZ,
               const Color &color = Color(0.5, 0.5, 0.5, 1), float lineWidth = 1)
        : _sizeX(sizeX), _sizeZ(sizeZ), _segmentsX(segmentsX), _segmentsZ(segmentsZ),
          _color(color), _lineWidth(lineWidth) {}

protected:
    virtual void render() {
        glLineWidth(_lineWidth);
        glBegin(GL_LINES);
        {
            glColor3d(_color.r, _color.g, _color.b);
            for (int indexX = 0; indexX < _segmentsX + 1; indexX++) {
                double x = ((double)indexX / _segmentsX - 0.5) * _sizeX;
                glVertex3d(x, 0.0,  _sizeZ / 2);
                glVertex3d(x, 0.0, -_sizeZ / 2);
            }
            for (int indexZ = 0; indexZ < _segmentsZ + 1; indexZ++) {
                double z = ((double)indexZ / _segmentsZ - 0.5) * _sizeZ;
                glVertex3d( _sizeX / 2, 0.0, z);
                glVertex3d(-_sizeX / 2, 0.0, z);
            }
        }
        glEnd();
    }

    double _sizeX;
    double _sizeZ;
    double _segmentsX;
    double _segmentsZ;
    Color _color;
    float _lineWidth;
};

} // namespace pgl
