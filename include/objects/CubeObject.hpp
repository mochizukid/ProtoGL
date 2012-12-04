#pragma once

#include <GL/freeglut.h>
#include "core/Object3D.hpp"
#include "core/Vector3.hpp"
#include "core/Material.hpp"

namespace pgl {

class CubeObject : public Object3D {
public:
    CubeObject(double size, Material *material)
        : _size(size) {

        _material = material;
    }

protected:
    virtual void render() {
        glutSolidCube(_size);
    }

    double _size;
};

} // namespace pgl
