#include "spiral.h"

Spiral::Spiral(double radius, double step)
{
    if(radius > 0 && step > 0)
    {
        this->radius = radius;
        this->step = step;
    }
}

Point Spiral::get_point(double t)
{
    double x = radius * cos(t);
    double y = radius * sin(t);
    double z = step * t / (2 * M_PI);

    return Point(x, y, z);
}

Point Spiral::get_derivative(double t)
{
    double dx = -radius * sin(t);
    double dy = radius * cos(t);
    double dz = step / (2 * M_PI);

    return Point(dx, dy, dz);
}
