#pragma once

#include <assert.h>
#include <GL/freeglut.h>
#include "core/Scene.hpp"
#include "core/Camera.hpp"
#include "core/Color.hpp"

namespace pgl {

class Renderer {
public:
    Renderer() : _viewportWidth(0), _viewportHeigth(0) {}

    void SetViewportSize(int width, int height) {
        _viewportWidth = width;
        _viewportHeigth = height;
        
        glViewport(0, 0, width, height);
    }

    void SetClearColor(const Color &clearColor) {
        _clearColor = clearColor;
        glClearColor((float)_clearColor.r, (float)_clearColor.g, (float)_clearColor.b, (float)_clearColor.a);
    }
    
    void Render(Scene *scene, Camera *camera) {
        camera->UpdateProjectionMatrix();
        scene->Render();
    }

    
protected:
    Color _clearColor;
    double _viewportWidth;
    double _viewportHeigth;
};

} // namespace pgl
