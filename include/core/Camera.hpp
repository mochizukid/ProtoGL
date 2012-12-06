#pragma once

#include <GL/freeglut.h>

#include "core/Vector3.hpp"
#include "core/Object3D.hpp"

namespace pgl {

class Camera {
public:
    Camera() : _type(PERSPECTIVE), _fovy(0), _aspect(0), _zNear(0), _zFar(0) {
        _up.Set(0, 1, 0);
        _target.Set(0, 0, 0);
        _position.Set(3, 4, 5);
    }

    void SetupPerspectiveCamera(double fovy, double aspect, double zNear, double zFar) {
        _type = PERSPECTIVE;
        _fovy = fovy;
        _aspect = aspect;
        _zNear = zNear;
        _zFar = zFar;
    }

    void SetupOrthographicCamera(double left, double right, double top, double bottom, double near, double far);

    void SetAspectRatio(double aspect) {
        _aspect = aspect;
    }
        
    void SetPosition(double x, double y, double z) {
        _position.Set(x, y, z);
    }
    
    void SetPosition(const Vector3 &v) {
        _position = v;
    }
    
    const Vector3 &GetPosition() const { return _position; }
    
    void LookAt(const Vector3 &v) {
        _target = v;
    }
    const Vector3 &GetTarget() const { return _target; }
    
    const Vector3 &GetUp() const { return _up; }

    // TODO: target を中心に移動するメソッド(左ドラッグに連動)
    // TODO: target に近づく/離れるメソッド(マウスホイールに連動)
    // TODO: 平行移動するメソッド(右ドラッグに連動)
    
    void UpdateProjectionMatrix() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(_fovy, _aspect, _zNear, _zFar);
        gluLookAt(_position.x, _position.y, _position.z, 
                  _target.x, _target.y, _target.z, 
                  _up.x, _up.y, _up.z);
    }

protected:
    enum Type { PERSPECTIVE, ORTHOGRAPHIC };

    Type _type;
    double _fovy;
    double _aspect;
    double _zNear;
    double _zFar;
    Vector3 _position;
    Vector3 _up;
    Vector3 _target;
};


} // namespace pgl

