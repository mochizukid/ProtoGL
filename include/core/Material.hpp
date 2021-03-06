#pragma once

#include <GL/freeglut.h>
#include <string.h>
#include "Color.hpp"

namespace pgl {

class Material {
public:
    enum Type {
        EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQUOISE,
        BRASS, BRONZE, CHROME, COPPER, GOLD, SILVER,
        BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC,
        BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER,
        TYPE_NUM
    };

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
        array[0] = (float)color.r; 
		array[1] = (float)color.g; 
		array[2] = (float)color.b; 
		array[3] = (float)color.a;
    }
    
    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _shininess;
};

/*
 * These numbers come from the OpenGL teapots.c demo
 * (c) Copyright 1993. Silicon Graphics, Inc.
 * (c) Mark J. Kilgard. 1994.
 */
const Material::MaterialData Material::MATERIALS[Material::TYPE_NUM] = {
    {
        {0.0215f, 0.1745f, 0.0215f},
        {0.07568f, 0.61424f, 0.07568f},
        {0.633f, 0.727811f, 0.633f},
        0.6f,
    },
    {
        {0.135f, 0.2225f, 0.1575f},
        {0.54f, 0.89f, 0.63f},
        {0.316228f, 0.316228f, 0.316228f},
        0.1f,
    },
    {
        {0.05375f, 0.05f, 0.06625f},
        {0.18275f, 0.17f, 0.22525f},
        {0.332741f, 0.328634f, 0.346435f},
        0.3f,
    },
    {
        {0.25f, 0.20725f, 0.20725f},
        {1.f, 0.829f, 0.829f},
        {0.296648f, 0.296648f, 0.296648f},
        0.088f,
    },
    {
        {0.1745f, 0.01175f, 0.01175f},
        {0.61424f, 0.04136f, 0.04136f},
        {0.727811f, 0.626959f, 0.626959f},
        0.6f,
    },
    {
        {0.1f, 0.18725f, 0.1745f},
        {0.396f, 0.74151f, 0.69102f},
        {0.297254f, 0.30829f, 0.306678f},
        0.1f,
    },
    {
        {0.329412f, 0.223529f, 0.027451f},
        {0.780392f, 0.568627f, 0.113725f},
        {0.992157f, 0.941176f, 0.807843f},
        0.21794872f,
    },
    {
        {0.2125f, 0.1275f, 0.054f},
        {0.714f, 0.4284f, 0.18144f},
        {0.393548f, 0.271906f, 0.166721f},
        0.2f,
    },
    {
        {0.25f, 0.25f, 0.25f},
        {0.4f, 0.4f, 0.4f},
        {0.774597f, 0.774597f, 0.774597f},
        0.6f,
    },
    {
        {0.19125f, 0.0735f, 0.0225f},
        {0.7038f, 0.27048f, 0.0828f},
        {0.256777f, 0.137622f, 0.086014f},
        0.1f,
    },
    {
        {0.24725f, 0.1995f, 0.0745f},
        {0.75164f, 0.60648f, 0.22648f},
        {0.628281f, 0.555802f, 0.366065f},
        0.4f,
    },
    {
        {0.19225f, 0.19225f, 0.19225f},
        {0.50754f, 0.50754f, 0.50754f},
        {0.508273f, 0.508273f, 0.508273f},
        0.4f,
    },
    {
        {0.0f, 0.0f, 0.0f},
        {0.01f, 0.01f, 0.01f},
        {0.50f, 0.50f, 0.50f},
        .25f,
    },
    {
        {0.0f, 0.1f, 0.06f},
        {0.0f, 0.50980392f, 0.50980392f},
        {0.50196078f, 0.50196078f, 0.50196078f},
        .25f,
    },
    {
        {0.0f, 0.0f, 0.0f},
        {0.1f, 0.35f, 0.1f},
        {0.45f, 0.55f, 0.45f},
        .25f,
    },
    {
        {0.0f, 0.0f, 0.0f},
        {0.5f, 0.0f, 0.0f},
        {0.7f, 0.6f, 0.6f},
        .25f,
    },
    {
        {0.0f, 0.0f, 0.0f},
        {0.55f, 0.55f, 0.55f},
        {0.70f, 0.70f, 0.70f},
        .25f,
    },
    {
        {0.0f, 0.0f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {0.60f, 0.60f, 0.50f},
        .25f,
    },
    {
        {0.02f, 0.02f, 0.02f},
        {0.01f, 0.01f, 0.01f},
        {0.4f, 0.4f, 0.4f},
        .078125f,
    },
    {
        {0.0f, 0.05f, 0.05f},
        {0.4f, 0.5f, 0.5f},
        {0.04f, 0.7f, 0.7f},
        .078125f,
    },
    {
        {0.0f, 0.05f, 0.0f},
        {0.4f, 0.5f, 0.4f},
        {0.04f, 0.7f, 0.04f},
        .078125f,
    },
    {
        {0.05f, 0.0f, 0.0f},
        {0.5f, 0.4f, 0.4f},
        {0.7f, 0.04f, 0.04f},
        .078125f,
    },
    {
        {0.05f, 0.05f, 0.05f},
        {0.5f, 0.5f, 0.5f},
        {0.7f, 0.7f, 0.7f},
        .078125f,
    },
    {
        {0.05f, 0.05f, 0.0f},
        {0.5f, 0.5f, 0.4f},
        {0.7f, 0.7f, 0.04f},
        .078125f,
    },
};

} // namespace pgl
