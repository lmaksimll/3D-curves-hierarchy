#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(double x, double y, double z);

    double get_coord_x();
    double get_coord_y();
    double get_coord_z();

private:
    double x;
    double y;
    double z;
};

#endif // POINT_H
