#include <stdio.h>
#include "ProtoGL.hpp"

using namespace pgl;

static const double WINDOW_W = 600, WINDOW_H = 400;

class SampleView : public View {
public:
    SampleView() : _rotate(0) {}

protected:
    virtual bool onCreate(void) {
        /*
         * setup camera
         */
        _camera.SetupPerspectiveCamera(30.0, (double)WINDOW_W / WINDOW_H, 0.1, 100);
        _camera.SetPosition(6.0, 8.0, 10.0);

        /*
         * create objects & light
         */
        Light *light = new Light();
        Object3D *grid = new GridObject(10, 10, 20, 20);
        Object3D *axis = new AxisObject(5);
        Object3D *cube = new CubeObject(1, new Material());
        Object3D *cube2 = new CubeObject(0.5, Material::Create(Material::EMERALD));
        Object3D *sphere = new SphereObject(0.2, Material::Create(Material::RUBY));

        _cube = cube;
        _cube2 = cube2;

        /*
         * setup scene graph
         */
        light->SetPosition(0, 10, 0, 1);
        cube->Translate(1, 0.5, 0);
        cube2->Translate(2, 0, 0);
        sphere->Translate(0, 1, 0);

        _scene.AddLight(light);
        _scene.AddObject(grid);
        _scene.AddObject(axis);
        _scene.AddObject(cube);

        cube->Add(cube2);
        cube2->Add(sphere);


        Application::StartAnimationLoop(30);
        return true;
    }

    virtual bool onDisplay(void) {
        _cube->SetRotationY(_rotate);
        _cube2->SetRotationX(_rotate);
        _rotate += 2;
        return true;
    }

private:
    double _rotate;
    Object3D *_cube;
    Object3D *_cube2;
};

int
main(int argc, char *argv[])
{
    Log::SetLevel(Log::LEVEL_DEBUG);
    
    SampleView view;
    Application::Start(argc, argv, &view, WINDOW_W, WINDOW_H);
    return 0;
}

