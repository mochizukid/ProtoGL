namespace pgl {

#include <GL/freeglut.h>
#include "core/Object3D.hpp"
#include "core/Material.hpp"
    
class SphereObject : public Object3D {
public:
    SphereObject(double radius, Material *material, int slices = 20, int stacks = 10)
        : _radius(radius), _slices(slices), _stacks(stacks) {

        _material = material;
    }

protected:
    virtual void render() {
        glutSolidSphere(_radius, _slices, _stacks);
    }
    
    double _radius;
    int _slices;
    int _stacks;
};

} // namespace pgl
