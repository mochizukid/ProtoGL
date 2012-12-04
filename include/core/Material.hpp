#pragma once

#include "Color.hpp"

namespace pgl {

class Material {
public:
    Material(const Color &ambient = Color(0.2, 0.2, 0.2, 1), const Color &diffuse = Color(0.8, 0.8, 0.8, 1), 
             const Color &specular = Color(0, 0, 0, 1), float shininess = 0) {

        setArray4(_ambient, ambient);
        setArray4(_diffuse, diffuse);
        setArray4(_specular, specular);
        _shininess = shininess;
    }

    void Apply() {
        glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, _specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, &_shininess);
    }
    
protected:
    static void setArray4(float *array, const Color &color) {
        array[0] = color.r; array[1] = color.g; array[2] = color.b; array[3] = color.a;
    }
    
    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _shininess;
};

} // namespace pgl
