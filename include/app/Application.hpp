#pragma once

#include <assert.h>
#include <GL/freeglut.h>
#include "app/View.hpp"
#include "core/Renderer.hpp"

namespace pgl {

class Application {
public:
    static void Start(int &argc, char *argv[],
                      View *view, int windowWidth = 400, int windowHeight = 400) {
        if (_app == NULL) {
            _app = new Application(argc, argv, view, windowWidth, windowHeight);
        }
    }

    static void StartAnimationLoop() {
        glutIdleFunc(IdleFunc);
    }

    static void StopAnimationLoop() {
        glutIdleFunc(NULL);
    }

private:
    static void DisplayFunc(void) {
        _view->OnDisplay();
        glutSwapBuffers();
    }
    
    static void KeyboardFunc(unsigned char key, int x, int y) {
        _view->OnKeyboard(key, x, y);
    }
    
    static void KeyboardUpFunc(unsigned char key, int x, int y) {
        _view->OnKeyboardUp(key, x, y);
    }

    static void SpecialFunc(int key, int x, int y) {
        _view->OnSpecial(key, x, y);
    }
    
    static void SpecialUpFunc(int key, int x, int y) {
        _view->OnSpecialUp(key, x, y);
    }
    
    static void MouseFunc(int button, int state, int x, int y) {
        _view->OnMouse(button, state, x, y);
    }
    
    static void MotionFunc(int x, int y) {
        _view->OnMouseMove(x, y);
    }
    
    static void MouseWheelFunc(int wheelNumber, int direction, int x, int y) {
        _view->OnMouseWheel(wheelNumber, direction, x, y);
    }
    
    static void ReshapeFunc(int w, int h) {
        _view->OnResize(w, h);
    }
    
    static void CloseFunc() {
        _view->OnDestroy();
    }

    static void IdleFunc(void) {
        glutPostRedisplay();
    }
    
    Application(int &argc, char *argv[], View *view, int windowWidth, int windowHeight) {
        assert(view != NULL);
        
        _view = view;
            
        glutInit(&argc, argv);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        glutInitWindowSize(windowWidth, windowHeight);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("ProtoGL");

        glEnable(GL_DEPTH_TEST);

        // set callback functions
        glutDisplayFunc(DisplayFunc);
        glutKeyboardFunc(KeyboardFunc);
        glutKeyboardUpFunc(KeyboardUpFunc);
        glutSpecialFunc(SpecialFunc);
        glutSpecialUpFunc(SpecialUpFunc);
        glutMouseFunc(MouseFunc);
        glutMotionFunc(MotionFunc);
        glutMouseWheelFunc(MouseWheelFunc);
        
        glutReshapeFunc(ReshapeFunc);
        glutCloseFunc(CloseFunc);

        _view->OnCreate();

        glutMainLoop();
    }

    static Application *_app;
    static View *_view;
};

Application *Application::_app = NULL;
View *Application::_view = NULL;

} // namespace pgl
