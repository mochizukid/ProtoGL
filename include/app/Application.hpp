#pragma once

#include <assert.h>
#include <GL/freeglut.h>
#include "app/View.hpp"
#include "core/Renderer.hpp"

namespace pgl {

class Application {
public:
    static void Start(int &argc, char *argv[],
                      View *view, int width = 400, int height = 400, const char *title = "ProtoGL") {
        if (_app == NULL) {
            _app = new Application(argc, argv, view, width, height, title);
        }
    }

    static void StartAnimationLoop(int fps = 30) {
        assert(fps >= 0);
        _tick_ms = 1000 / fps;
        
        glutIdleFunc(IdleFunc);
    }

    static void StopAnimationLoop() {
        glutIdleFunc(NULL);
    }

private:
    static void DisplayFunc(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        int now = glutGet(GLUT_ELAPSED_TIME);
        
        if (now - _prev_time > _tick_ms) {
            glutPostRedisplay();
	        _prev_time = now;
        }
    }
    
    Application(int &argc, char *argv[], View *view, int width, int height, const char *title) {
        assert(view != NULL);
        assert(width != 0 && height != 0 && title != NULL);
        
        _view = view;
            
        glutInit(&argc, argv);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        glutInitWindowSize(width, height);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow(title);

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
    static int _tick_ms;
    static int _prev_time;
};

Application *Application::_app = NULL;
View *Application::_view = NULL;
int Application::_tick_ms = 0;
int Application::_prev_time = 0;

} // namespace pgl
