#ifndef CURVE_H
#define CURVE_H
#include "point.h"

class Curve
{
public:
    virtual Point get_point(double t) = 0;
    virtual Point get_derivative(double t) = 0;
};

#endif // CURVE_H
