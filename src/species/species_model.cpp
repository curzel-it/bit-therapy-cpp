#include "species_model.h"

#include <string>

Species::Species(std::string id, double speed, double scale) : 
    id(id), 
    speed(speed), 
    scale(scale) 
{
    this->dragPath = "drag";
    this->movementPath = "walk";
    this->zIndex = 0.0;
}

SpeciesAnimation::SpeciesAnimation(std::string id, std::string position, std::vector<double> size) : 
    id(id), 
    position(position), 
    size(size) 
{}
