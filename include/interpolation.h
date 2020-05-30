#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <vector>
#include "point.h"
#include "point_collection.h"

using std::vector;

namespace interpolation
{

class Linear
{
public:
    Linear(const PointCollection& _points);

    // Overload () operator for this class. Now we can use an object of the class as a function!
    double operator() (double x);

private:
    PointCollection points;
    vector<double> dx, dy;
    size_t N_elem;
};

class Polynomial
{
public:
    Polynomial(const PointCollection& _points);

    // Overload () operator for this class. Now we can use an object of the class as a function!
    double operator() (double x);

    double Lagrange(size_t index, double x, const PointCollection& points);

private:
    PointCollection points;
    vector<double> dx, dy;
    size_t N_elem;
};

}

#endif // INTERPOLATION_H
