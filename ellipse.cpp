#include "ellipse.h"

Ellipse::Ellipse(double radius_x, double radius_y)
{
    if(radius_x > 0 && radius_y > 0)
    {
        this->radius_x = radius_x;
        this->radius_y = radius_y;
    }
}

Point Ellipse::get_point(double t)
{
    double x = radius_x * cos(t);
    double y = radius_y * sin(t);

    return Point(x, y, 0);
}

Point Ellipse::get_derivative(double t)
{
    double dx = -radius_x * sin(t);
    double dy = radius_y * cos(t);

    return Point(dx, dy, 0);
}
