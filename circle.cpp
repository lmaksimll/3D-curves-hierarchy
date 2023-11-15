#include "circle.h"

Circle::Circle(double radius)
{
    if(radius > 0)
    {
        this->radius = radius;
    }
}

Point Circle::get_point(double t)
{
    double x = radius * cos(t);
    double y = radius * sin(t);

    return Point(x, y, 0);
}

Point Circle::get_derivative(double t)
{
    double dx = -radius * sin(t);
    double dy = radius * cos(t);

    return Point(dx, dy, 0);
}
