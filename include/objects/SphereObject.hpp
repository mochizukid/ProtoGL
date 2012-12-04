namespace pgl {

class SphereObject : public Object3D {
public:
    SphereObject(double radius, int slices = 20, int stacks = 10) 
        : _radius(radius), _slices(slices), _stacks(stacks) {}

protected:
    
    virtual void render() {
        glBegin(GL_LINES);
        {
            glutWireSphere(_radius, _slices, _stacks);
            //glutSolidSphere(_radius, _slices, _stacks);
        }
        glEnd();
    }
    
    double _radius;
    int _slices;
    int _stacks;
};

} // namespace pgl
