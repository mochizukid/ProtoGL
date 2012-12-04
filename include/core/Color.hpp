#pragma once

namespace pgl {

class Color {
public:
    Color() : r(0), g(0), b(0), a(0) {}
    Color(double r, double g, double b, double a = 1)
        : r(r), g(g), b(b), a(a) {}

    void Set(double r, double g, double b, double a = 1) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    double r;
    double g;
    double b;
    double a;
};


} // namespace pgl

