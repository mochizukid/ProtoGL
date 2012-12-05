#pragma once

#include <assert.h>
#include <GL/freeglut.h>
#include "core/Renderer.hpp"
#include "core/Quaternion.hpp"
#include "core/Log.hpp"

namespace pgl {

class View {
public:
    View() : _prevMouseX(0), _prevMouseY(0), _isDraggingL(false), _doShowCameraPos(false) {}

    void OnCreate(void) {
        Log::Verbose("View::OnCreate()");

        if (!onCreate()) {
            return; // prevent default
        }
    }
    
    void OnDestroy(void) {
        Log::Verbose("View::OnDestroy()");
        
        if (!onDestroy()) {
            return; // prevent default
        }
    }
    
    void OnDisplay(void) {
        Log::Verbose("View::OnDisplay()");

        if (!onDisplay()) {
            return; // prevent default
        }
        
        _renderer.Render(&_scene, &_camera);
    }
    
    void OnKeyboard(unsigned char key, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnKeyboard(%d, %d, %d)", key, x, y);
        Log::Verbose(msg);

        if (!onKeyboard(key, x, y)) {
            return; // prevent default
        }
        
        switch (key) {
        case 'd':
            _doShowCameraPos = !_doShowCameraPos;
            break;

        case 0x1B: // ESC
            glutLeaveMainLoop();
            break;

        default:
            break;
        }
    }

    virtual void OnKeyboardUp(unsigned char key, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnKeyboardUp(%d, %d, %d)", key, x, y);
        Log::Verbose(msg);

        if (!onKeyboardUp(key, x, y)) {
            return; // prevent default
        }
    }

    virtual void OnSpecial(int key, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnSpecial(%d, %d, %d)", key, x, y);
        Log::Verbose(msg);

        if (!onSpecial(key, x, y)) {
            return; // prevent default
        }
        
        switch (key) {
        case GLUT_KEY_F11:
            glutFullScreenToggle();

        default:
            break;
        }
    }

    virtual void OnSpecialUp(int key, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnSpecialUp(%d, %d, %d)", key, x, y);
        Log::Verbose(msg);

        if (!onSpecialUp(key, x, y)) {
            return; // prevent default
        }
    }
    
    virtual void OnMouse(int button, int state, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnMouse(%d, %d, %d, %d)", button, state, x, y);
        Log::Verbose(msg);

        if (!onMouse(button, state, x, y)) {
            return; // prevent default
        }
        
        switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                _prevMouseX = x;
                _prevMouseY = y;
                _isDraggingL = true;
            }
            else if (state == GLUT_UP) {
                _isDraggingL = false;
            }
            break;

        case GLUT_MIDDLE_BUTTON:
            break;

        case GLUT_RIGHT_BUTTON:
            break;

        default:
            break;
        }

    }
    
    virtual void OnMouseMove(int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnMouseMove(%d, %d)", x, y);
        Log::Verbose(msg);
        
        if (!onMouseMove(x, y)) {
            return; // prevent default
        }
        
        if (!_isDraggingL) {
            return;
        }
        static int DX_PER_PI = 500;
        static int DY_PER_PI = 1000;

        double dx = x - _prevMouseX;
        double dy = y - _prevMouseY;
        _prevMouseX = x;
        _prevMouseY = y;

        const pgl::Vector3 &eye = _camera.GetPosition();
        const pgl::Vector3 &up = _camera.GetUp();
        const pgl::Vector3 &target = _camera.GetTarget();

        const pgl::Vector3 axisV = up;
        const pgl::Vector3 axisD = eye - target;
        const pgl::Vector3 axisH = pgl::Vector3::Cross(axisV, axisD);

        if (_isDraggingL) {
            pgl::Vector3 dst1, dst2;
            pgl::Quaternion::RotatePoint(eye, dx * M_PI / DX_PER_PI, axisV, dst1);
            pgl::Quaternion::RotatePoint(dst1, dy * M_PI / DY_PER_PI, axisH, dst2);
            _camera.SetPosition(dst2);

            if (_doShowCameraPos) {
                sprintf(msg, "Camera pos = (%.2f, %.2f, %.2f)\n", dst2.x, dst2.y, dst2.z);
                Log::Print(msg);
            }
        }

        glutPostRedisplay();
    }

    virtual void OnMouseWheel(int wheelNumber, int direction, int x, int y) {
        char msg[256];
        sprintf(msg, "View::OnMouseWheel(%d, %d, %d, %d)", wheelNumber, direction, x, y);
        Log::Verbose(msg);

        if (!onMouseWheel(wheelNumber, direction, x, y)) {
            return; // prevent default
        }
    }
    
    virtual void OnResize(int w, int h) {
        char msg[256];
        sprintf(msg, "View::OnResize(%d, %d)", w, h);
        Log::Verbose(msg);
        
        if (!onResize(w, h)) {
            return; // prevent default
        }
        
        _renderer.SetViewportSize(w, h);
        
        _camera.SetAspectRatio((double)w / h);
    }

protected:
    virtual bool onCreate(void) { return true; }
    virtual bool onDestroy(void) { return true; }
    virtual bool onDisplay(void) { return true; }
    virtual bool onKeyboard(unsigned char key, int x, int y) { return true; }
    virtual bool onKeyboardUp(unsigned char key, int x, int y) { return true; }
    virtual bool onSpecial(int key, int x, int y) { return true; }
    virtual bool onSpecialUp(int key, int x, int y) { return true; }
    virtual bool onMouse(int button, int state, int x, int y) { return true; }
    virtual bool onMouseMove(int x, int y) { return true; }
    virtual bool onMouseWheel(int wheelNumber, int direction, int x, int y) { return true; }
    virtual bool onResize(int w, int h) { return true; }

    Camera _camera;
    Scene _scene;
    Renderer _renderer;

    int _prevMouseX;
    int _prevMouseY;
    bool _isDraggingL;
    bool _doShowCameraPos;
    
};


} // namespace pgl
