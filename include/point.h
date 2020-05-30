#ifndef POINT_H
#define POINT_H
#include <ostream>

struct Point
{
    double x, y;
};


inline std::ostream& operator << (std::ostream& os, const Point& p)
{
    return os << "(" << p.x << "," << p.y << ")";
}

inline bool operator < (Point a, Point b) { return a.x < b.x; }

#endif // POINT_H
