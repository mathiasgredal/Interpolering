#include "interpolation.h"
#include <algorithm>
#include <string>
#include <stdexcept>

namespace interpolation
{

Linear::Linear(const PointCollection& _points)
{
    if(!std::is_sorted(_points.begin(),_points.end())) throw std::runtime_error("X-values should be in ascending order.");
    points = _points;
    N_elem = points.size();

    dx = vector<double>(N_elem,0);
    dy = dx;

    for(size_t k = 1; k < N_elem; k++)
    {
        dx[k] = points[k].x - points[k-1].x;
        dy[k] = points[k].y - points[k-1].y;
    }
}

double Linear::operator() (double x_in)
{
    size_t index = 0;
    for(size_t k = 0; k < N_elem; k++)
    {
        if(points[k].x >= x_in)
        {
            index = k;
            break;
        }
    }
    if(index == 0)
    {
        return points[0].y;
    }
    size_t prev = index-1;
    return dy[index] * (x_in-points[prev].x)/dx[index] + points[prev].y;
}

Polynomial::Polynomial(const PointCollection& _points)
{
    if(!std::is_sorted(_points.begin(),_points.end())) throw std::runtime_error("X-values should be in ascending order.");
    points = _points;
    N_elem = points.size();

    dx = vector<double>(N_elem,0);
    dy = dx;

    for(size_t k = 1; k < N_elem; k++)
    {
        dx[k] = points[k].x - points[k-1].x;
        dy[k] = points[k].y - points[k-1].y;
    }
}

double Polynomial::operator() (double x_in)
{
    double y = 0;
    for(size_t i = 0; i < points.size(); i++)
    {
        y+=points.at(i).y*Lagrange(i, x_in, points);
    }

    return y;
}

double Polynomial::Lagrange(size_t index, double x, const PointCollection& points)
{
    vector<double> lagranges = {};

    for(size_t i = 0; i < points.size(); i++)
    {
        if(i == index)
            continue;

        lagranges.push_back((x-points.at(i).x)/(points.at(index).x-points.at(i).x));
    }

    double lagrange = lagranges.front();
    for(const auto& i : lagranges)
    {
        lagrange *= i;
    }

    return lagrange;
}

}
