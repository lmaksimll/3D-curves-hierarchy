#include "point.h"

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Point::get_coord_x()
{
    return this->x;
}

double Point::get_coord_y()
{
    return this->y;
}

double Point::get_coord_z()
{
    return this->z;
}
