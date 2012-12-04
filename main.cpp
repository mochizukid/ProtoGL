#include <stdio.h>
#include "ProtoGL.hpp"

#define WINDOW_W 600
#define WINDOW_H 400

class SampleView : public pgl::View {
public:
    virtual void OnCreate() {
        View::OnCreate();
        
        _camera.SetupPerspectiveCamera(30.0, (double)WINDOW_W / WINDOW_H, 0.1, 100);
        _camera.SetPosition(6.0, 8.0, 10.0);

        /*
         * add objects
         */
        pgl::Object3D *gridObj = new pgl::GridObject(10, 10, 20, 20);
        _scene.AddObject(gridObj);
        
        pgl::Object3D *axisObj = new pgl::AxisObject(5);
        _scene.AddObject(axisObj);

        pgl::Material *material = new pgl::Material(pgl::Color(0.1, 1, 0.8, 1));
        pgl::Object3D *cubeObj = new pgl::CubeObject(1, material);
        _scene.AddObject(cubeObj);

        cubeObj->RotateY(30);
        cubeObj->Translate(1, 0.5, 0);

        pgl::Material *material2 = new pgl::Material();
        pgl::Object3D *cubeObj2 = new pgl::CubeObject(0.5, material2);
        cubeObj->Add(cubeObj2);

        cubeObj2->Translate(2, 0, 0);
        cubeObj2->RotateY(30);

        //pgl::Object3D *sphereObj = new pgl::SphereObject(2);
        //_scene.AddObject(sphereObj);

        /*
         * add lights
         */
        pgl::Light *light = new pgl::Light(pgl::Color(1, 1, 1), pgl::Color(1, 0.5, 0.5));
        light->SetPosition(0, 10, 0, 1);
        _scene.AddLight(light);

        
        //pgl::Application::StartAnimationLoop();
    }

    virtual void OnDisplay() {
        View::OnDisplay();

        // TODO:
    }

};

int
main(int argc, char *argv[])
{
    //pgl::Log::SetLevel(pgl::Log::ERROR);
    
    SampleView view;
    pgl::Application::Start(argc, argv, &view, WINDOW_W, WINDOW_H);
}

