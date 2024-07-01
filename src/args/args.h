#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Arguments {
    bool help = false;
    bool debug = false;
    double scale = 1.0;
    double speed = 1.0;
    std::vector<std::string> species;
    std::vector<std::string> screens;
};

Arguments parseArgs(int argc, char* argv[]);
