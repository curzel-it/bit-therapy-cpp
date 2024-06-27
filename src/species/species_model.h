#pragma once

#include <string>

struct Species {
public:
    std::string id;
    double speed;
    double scale;

    Species(std::string id, double speed, double scale);
};

}