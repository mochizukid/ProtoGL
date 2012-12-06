#pragma once

#include <GL/freeglut.h>
#include <assert.h>
#include <list>
#include "core/Vector3.hpp"
#include "core/Material.hpp"

namespace pgl {

class Object3D {
public:
    Object3D() : _parent(NULL), _needUpdateMatrix(false), _material(NULL) {
        _scale.Set(1, 1, 1);
    }

    virtual ~Object3D() {
        if (_material) {
            delete _material;
        }
        for (std::list<Object3D *>::iterator it = _children.begin(); it != _children.end(); it++) {
            delete *it;
        }
    }
    
    void SetPosition(const Vector3 &v) { _position = v; _needUpdateMatrix = true; }
    void SetPositionX(double x) { _position.x = x; _needUpdateMatrix = true; }
    void SetPositionY(double y) { _position.y = y; _needUpdateMatrix = true; }
    void SetPositionZ(double z) { _position.z = z; _needUpdateMatrix = true; }
    const Vector3 &GetPosition() const { return _position; }
    
    void SetRotation(const Vector3 &v) { _rotation = v; _needUpdateMatrix = true; }
    void SetRotationX(double x) { _rotation.x = x; _needUpdateMatrix = true; }
    void SetRotationY(double y) { _rotation.y = y; _needUpdateMatrix = true; }
    void SetRotationZ(double z) { _rotation.z = z; _needUpdateMatrix = true; }
    const Vector3 &GetRotation() const { return _rotation; }
    
    void SetScale(const Vector3 &v) { _scale = v; _needUpdateMatrix = true; }
    void SetScaleX(double x) { _scale.x = x; _needUpdateMatrix = true; }
    void SetScaleY(double y) { _scale.y = y; _needUpdateMatrix = true; }
    void SetScaleZ(double z) { _scale.z = z; _needUpdateMatrix = true; }
    const Vector3 &GetScale() const { return _scale; }
    
    void Translate(double dx, double dy, double dz) {
        TranslateX(dx);
        TranslateY(dy);
        TranslateZ(dz);
    }
    void TranslateX(double dx) { _position.x += dx; _needUpdateMatrix = true; }
    void TranslateY(double dy) { _position.y += dy; _needUpdateMatrix = true; }
    void TranslateZ(double dz) { _position.z += dz; _needUpdateMatrix = true; }

    void Rotate(double dx, double dy, double dz) {
        RotateX(dx);
        RotateY(dy);
        RotateZ(dz);
    }
    void RotateX(double dx) { _rotation.x += dx; _needUpdateMatrix = true; }
    void RotateY(double dy) { _rotation.y += dy; _needUpdateMatrix = true; }
    void RotateZ(double dz) { _rotation.z += dz; _needUpdateMatrix = true; }

    void Scale(double dx, double dy, double dz) {
        ScaleX(dx);
        ScaleY(dy);
        ScaleZ(dz);
    }
    void ScaleX(double dx) { _scale.x *= dx; _needUpdateMatrix = true; }
    void ScaleY(double dy) { _scale.y *= dy; _needUpdateMatrix = true; }
    void ScaleZ(double dz) { _scale.z *= dz; _needUpdateMatrix = true; }

    void Add(Object3D *obj) {
        assert(obj != NULL && obj != this);
        _children.push_back(obj);
    }

    void Remove(Object3D *obj) {
        assert(obj != NULL && obj != this);
        _children.remove(obj);
    }

    void Render() {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            if (_material) {
                _material->Apply();
            }
            
            if (_needUpdateMatrix) {
                glTranslated(_position.x, _position.y, _position.z);
                glScaled(_scale.x, _scale.y, _scale.z);
                glRotated(_rotation.x, 1, 0, 0);
                glRotated(_rotation.y, 0, 1, 0);
                glRotated(_rotation.z, 0, 0, 1);
            }

            render();

            for (std::list<Object3D *>::iterator it = _children.begin(); it != _children.end(); it++) {
                (*it)->Render();
            }
        }
        glPopMatrix();
    }

    bool HasMaterial() {
        return (_material != NULL) ? true : false;
    }


protected:
    virtual void render() = 0;

    Object3D *_parent;
    Vector3 _position;
    Vector3 _rotation;
    Vector3 _scale;
    bool _needUpdateMatrix;
    std::list<Object3D *> _children;
    Material *_material;
};

} // namespace pgl
