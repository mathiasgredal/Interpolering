#include "data.h"


std::vector<PointCollection> data::Load_Points()
{
    std::ifstream data_file = std::ifstream("../data/data.txt");
    if(!data_file)
        throw std::runtime_error("Unable to open data file");

    std::vector<std::string> x_vals = {};
    std::vector<std::string> y_vals = {};

    std::string line;
    while (std::getline(data_file, line))
    {
        if(line.find("x:") == 0)
            x_vals.push_back(line.substr(3));
        else if (line.find("y:") == 0)
            y_vals.push_back(line.substr(3));
    }

    if(x_vals.size() != y_vals.size())
        throw std::runtime_error("Uneven number of x and y values");

    std::vector<PointCollection> point_collections = {};

    for(size_t i = 0; i < x_vals.size(); i++)
    {
        point_collections.push_back({});

        std::stringstream x;
        x << x_vals.at(i);
        std::stringstream y;
        y << y_vals.at(i);

        std::string x_num;
        std::string y_num;
        while (x >> x_num && y >> y_num)
        {
            point_collections.back().push_back({std::stod(x_num)+0.5, std::stod(y_num)+0.5});
        }
    }
    return point_collections;
}
