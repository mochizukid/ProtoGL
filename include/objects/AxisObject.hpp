#pragma once

#include <GL/freeglut.h>
#include "core/Object3D.hpp"
#include "core/Color.hpp"

namespace pgl {

class AxisObject : public Object3D {
public:
    AxisObject(double size, 
               const Color &colorX = Color(1, 0, 0),
               const Color &colorY = Color(0, 1, 0),
               const Color &colorZ = Color(0, 0, 1),
               float lineWidth = 2)
        : _size(size), _colorX(colorX), _colorY(colorY), _colorZ(colorZ), _lineWidth(lineWidth) {}

protected:

    virtual void render() {
        glLineWidth(_lineWidth);
        glBegin(GL_LINES);
        {
            // x-axis
            glColor3d(_colorX.r, _colorX.g, _colorX.b);
            glVertex3d(0, 0, 0);
            glVertex3d(_size, 0, 0);
            
            // y-axis
            glColor3d(_colorY.r, _colorY.g, _colorY.b);
            glVertex3d(0, 0, 0);
            glVertex3d(0, _size, 0);
            
            // z-axis
            glColor3d(_colorZ.r, _colorZ.g, _colorZ.b);
            glVertex3d(0, 0, 0);
            glVertex3d(0, 0, _size);
        }
        glEnd();
    }
    
    double _size;
    Color _colorX;
    Color _colorY;
    Color _colorZ;
    float _lineWidth;
};

} // namespace pgl
