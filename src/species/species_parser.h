#pragma once

#include <optional>
#include <string>
#include "nlohmann/json.hpp"
#include "species_model.h"
#include "species_parser.h"

class SpeciesParser {
public:
    std::optional<Species> parseFromFile(const std::string& filePath) const;
    std::optional<Species> parse(const std::string& jsonString) const;
};