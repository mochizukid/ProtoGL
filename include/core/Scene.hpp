#pragma once

#include <GL/freeglut.h>
#include <vector>
#include <list>
#include "core/Vector3.hpp"
#include "core/Object3D.hpp"
#include "core/Light.hpp"

namespace pgl {

class Scene {
public:
    virtual ~Scene() {
        for (std::list<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            delete *it;
        }
        for (std::list<Light *>::iterator it = _lights.begin(); it != _lights.end(); it++) {
            delete *it;
        }
    }
    
    void AddObject(Object3D *obj) {
        _objects.push_back(obj);
    }

    void RemoveObject(Object3D *obj) {
        _objects.remove(obj);
    }

    void AddLight(Light *light) {
        _lights.push_back(light);
    }

    void RemoveLight(Light *light) {
        _lights.remove(light);
    }

    virtual void Render() {
        /*
         * render with light
         */
        glEnable(GL_LIGHTING);
        for (std::list<Light *>::iterator it = _lights.begin(); it != _lights.end(); it++) {
            (*it)->On();
        }
        for (std::list<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object3D *obj = *it;
            if (obj->HasMaterial()) {
                obj->Render();
            }
        }
        for (std::list<Light *>::iterator it = _lights.begin(); it != _lights.end(); it++) {
            (*it)->Off();
        }
        glDisable(GL_LIGHTING);

        /*
         * render without light
         */
        for (std::list<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object3D *obj = *it;
            if (!obj->HasMaterial()) {
                obj->Render();
            }
        }
    }

    
protected:
    std::list<Object3D *> _objects;
    std::list<Light *> _lights;
};

} // namespace pgl
