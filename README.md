ProtoGL
=======

### What is ProtoGL? ###

This is a simple 3D framework based on OpenGL.


### Target users for ProtoGL ###

The target user for ProtoGL is the people who think:
- native OpenGL APIs are too low level
- full-scale 3D frameworks are too rich for simple prototyping


### Sample code ###

```c++
#include "ProtoGL.hpp"

using namespace pgl;

static const int WINDOW_W = 600, WINDOW_H = 400;

class SampleView : public View {
protected:
    virtual bool onCreate(void) {
        /*
         * setup camera
         */
        _camera.SetupPerspectiveCamera(30.0, WINDOW_W / WINDOW_H, 0.1, 100);
        _camera.SetPosition(6.0, 8.0, 10.0);

        /*
         * add objects & light
         */
        Light *light = new Light();
        Object3D *grid = new GridObject(10, 10, 20, 20);
        Object3D *axis = new AxisObject(5);
        Object3D *cube = new CubeObject(0.8, new Material());
        Object3D *sphere = new SphereObject(0.3, Material::Create(Material::RUBY));

        /*
         * setup scene graph
         */
        light->SetPosition(0, 10, 0, 1);
        cube->Translate(1, 1, 0);
        sphere->Translate(2, 0, 0);
        cube->RotateY(-30);

        _scene.AddLight(light);
        _scene.AddObject(grid);
        _scene.AddObject(axis);
        _scene.AddObject(cube);
        cube->Add(sphere);

        return true;
    }
};

int
main(int argc, char *argv[])
{
    SampleView view;
    Application::Start(argc, argv, &view, WINDOW_W, WINDOW_H);
    return 0;
}
```

![image](https://raw.github.com/mochizukid/ProtoGL/master/doc/screenshot.png)

  

### Install ###

1. Install freeglut and opengl
```shell
$ sudo apt-get install freeglut3 freegult3-dev
```

2. Just dd "ProtoGL/include" to your include path (since ProtoGL consists of header files only)


### Change log ###

**r1** - 2012/12/06

* initial release
