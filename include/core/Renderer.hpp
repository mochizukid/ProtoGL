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

    void SetViewportSize(double width, double height) {
        _viewportWidth = width;
        _viewportHeigth = height;
        
        glViewport(0, 0, width, height);
    }

    void SetClearColor(const Color &clearColor) {
        _clearColor = clearColor;
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    }
    
    void Render(Scene *scene, Camera *camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->UpdateProjectionMatrix();
        scene->Render();
    }

    
protected:
    Color _clearColor;
    double _viewportWidth;
    double _viewportHeigth;
};

} // namespace pgl
