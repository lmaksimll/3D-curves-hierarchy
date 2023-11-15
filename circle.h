#ifndef CIRCLE_H
#define CIRCLE_H
#include "curve.h"
#include <cmath>

class Circle : public Curve
{  
public:
    Circle(double radius);

    Point get_point(double t) override;
    Point get_derivative(double t) override;

private:
    double radius;
};

#endif // CIRCLE_H
