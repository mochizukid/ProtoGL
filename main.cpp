#include <stdio.h>
#include "ProtoGL.hpp"

#define WINDOW_W 600
#define WINDOW_H 400

class SampleView : public pgl::View {
public:
    SampleView() : _rotate(0) {}

protected:
    virtual bool onCreate(void) {
        _camera.SetupPerspectiveCamera(30.0, (double)WINDOW_W / WINDOW_H, 0.1, 100);
        _camera.SetPosition(6.0, 8.0, 10.0);

        /*
         * add objects
         */
        pgl::Object3D *grid = new pgl::GridObject(10, 10, 20, 20);
        _scene.AddObject(grid);
        
        pgl::Object3D *axis = new pgl::AxisObject(5);
        _scene.AddObject(axis);

        pgl::Material *material = new pgl::Material();
        pgl::Object3D *cube = new pgl::CubeObject(1, material);
        _scene.AddObject(cube);
        _cube = cube;

        cube->Translate(1, 0.5, 0);

        pgl::Material *material2 = pgl::Material::Create(pgl::Material::JADE);
        pgl::Object3D *cube2 = new pgl::CubeObject(0.5, material2);
        cube->Add(cube2);
        _cube2 = cube2;
        
        cube2->Translate(2, 0, 0);

        pgl::Material *material3 = pgl::Material::Create(pgl::Material::RUBY);
        pgl::Object3D *sphere = new pgl::SphereObject(0.2, material3);
        _cube2->Add(sphere);

        sphere->Translate(0, 1, 0);

        /*
         * add lights
         */
        pgl::Light *light = new pgl::Light();
        light->SetPosition(0, 10, 0, 1);
        _scene.AddLight(light);

        
        pgl::Application::StartAnimationLoop();

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
    pgl::Object3D *_cube;
    pgl::Object3D *_cube2;

};

int
main(int argc, char *argv[])
{
    pgl::Log::SetLevel(pgl::Log::VERBOSE);
    
    SampleView view;
    pgl::Application::Start(argc, argv, &view, WINDOW_W, WINDOW_H);
}

