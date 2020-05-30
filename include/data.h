#ifndef DATA_H
#define DATA_H
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "point.h"
#include "point_collection.h"

namespace data
{
    std::vector<PointCollection> Load_Points();

}

#endif // DATA_H
