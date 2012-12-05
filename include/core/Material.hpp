#pragma once

#include <string.h>
#include "Color.hpp"

namespace pgl {

class Material {
public:
    enum Type { JADE, RUBY, TYPE_NUM };
    /*
    enum Type {
        EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQUOISE, BRASS, BRONZE, CHROME, COPPER, GOLD, SILVER,
        BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC,
        BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER,
        TYPE_NUM
    };
     */
    struct MaterialData {
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float shininess;
    };

    static Material *Create(Type type) {
        return new Material(MATERIALS[type]);
    }

    
    Material(const Color &ambient = Color(0.2, 0.2, 0.2, 1), const Color &diffuse = Color(0.8, 0.8, 0.8, 1), 
             const Color &specular = Color(0, 0, 0, 1), float shininess = 0) {

        setArray4(_ambient, ambient);
        setArray4(_diffuse, diffuse);
        setArray4(_specular, specular);
        _shininess = shininess;
    }

    Material(const MaterialData &data) {
        size_t size = sizeof(float) * 4;
        memcpy(_ambient, data.ambient, size);
        memcpy(_diffuse, data.diffuse, size);
        memcpy(_specular, data.specular, size);
        _shininess = data.shininess;
    }

    void Apply() {
        glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, _specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, &_shininess);
    }
    
    static const MaterialData MATERIALS[TYPE_NUM];

protected:
    static void setArray4(float *array, const Color &color) {
        array[0] = color.r; array[1] = color.g; array[2] = color.b; array[3] = color.a;
    }
    
    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _shininess;
};

/*
 * These numbers come from the OpenGL teapots.c demo, (c) Silicon Graphics, Inc., (c) 1994, Mark J. Kilgard.
 */
const Material::MaterialData Material::MATERIALS[Material::TYPE_NUM] = {
    {
        {0.135,     0.2225,   0.1575,   1.0},
        {0.54,      0.89,     0.63,     1.0},
        {0.316228,  0.316228, 0.316228, 1.0},
        2.8,
    },
    {
        {0.1745,   0.01175,  0.01175,   1.0},
        {0.61424,  0.04136,  0.04136,   1.0},
        {0.727811, 0.626959, 0.626959,  1.0},
        6.8,
    },
};

} // namespace pgl
