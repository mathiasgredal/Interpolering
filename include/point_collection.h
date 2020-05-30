#ifndef POINTCOLLECTION_H
#define POINTCOLLECTION_H
#include <ostream>
#include <vector>
#include "point.h"

class PointCollection : public std::vector<Point>
{

};

inline std::ostream& operator << (std::ostream& os, const PointCollection& p)
{
    for(const auto& point : p)
    {
        os << "(" << point.x << "," << point.y << ") ";
    }

    return os;
}

#endif // POINTCOLLECTION_H
