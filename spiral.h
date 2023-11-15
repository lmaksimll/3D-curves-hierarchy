#ifndef SPIRAL_H
#define SPIRAL_H
#include "curve.h"
#include <cmath>

class Spiral : public Curve
{
public:
    Spiral(double radius, double step);

    Point get_point(double t) override;
    Point get_derivative(double t) override;

private:
    double radius;
    double step;
};

#endif // SPIRAL_H
