#pragma once

#include <GL/freeglut.h>

#include "Object3D.hpp"
#include "Vector3.hpp"
#include "Color.hpp"

namespace pgl {

class Light {
public:
    Light(const Color &ambient = Color(0.8, 0.8, 0.8, 1), const Color &diffuse = Color(1, 1, 1, 1),
          const Color &specular = Color(1, 1, 1, 1)) {
        
        _lightId = _nextLightId++;
        assert(_lightId < GL_LIGHT0 + GL_MAX_LIGHTS);

        setArray4(_ambient, ambient);
        setArray4(_diffuse, diffuse);
        setArray4(_specular, specular);
        setArray4(_position, 0, 0, 1, 0);
        setArray3(_spotDirection, 0, 0, -1);
    }

    virtual ~Light() {
        Off();
    }

    void On() {
        glEnable(_lightId);
        
        glLightfv(_lightId, GL_POSITION, _position);
        glLightfv(_lightId, GL_AMBIENT, _ambient);
        glLightfv(_lightId, GL_DIFFUSE, _diffuse);
        glLightfv(_lightId, GL_SPECULAR, _specular);
        glLightfv(_lightId, GL_SPOT_DIRECTION, _spotDirection);
    }
    
    void Off() {
        glDisable(_lightId);
    }

    void SetPosition(double x, double y, double z, double w) {
        setArray4(_position, x, y, z, w);
    }
    
protected:
    static void setArray3(float *array, float v0, float v1, float v2) {
        array[0] = v0; array[1] = v1; array[2] = v2;
    }
    
    static void setArray4(float *array, float v0, float v1, float v2, float v3) {
        array[0] = v0; array[1] = v1; array[2] = v2; array[3] = v3;
    }
    
    static void setArray4(float *array, const Color &color) {
        array[0] = color.r; array[1] = color.g; array[2] = color.b; array[3] = color.a;
    }
    
    static GLenum _nextLightId;

    GLenum _lightId;

    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _position[4];
    float _spotDirection[3];
};

GLenum Light::_nextLightId = GL_LIGHT0;

} // namespace pgl
