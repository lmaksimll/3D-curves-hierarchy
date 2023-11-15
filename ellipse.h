#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "curve.h"
#include <cmath>

class Ellipse : public Curve
{
public:
    Ellipse(double radius_x, double radius_y);

    Point get_point(double t) override;
    Point get_derivative(double t) override;

private:
    double radius_x;
    double radius_y;
};

#endif // ELLIPSE_H
