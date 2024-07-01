#include "args.h"

Arguments parseArgs(int argc, char* argv[]) {
    Arguments args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            args.help = true;
        } else if (arg == "--debug") {
            args.debug = true;
        } else if (arg == "--scale" && i + 1 < argc) {
            args.scale = std::stod(argv[++i]);
        } else if (arg == "--speed" && i + 1 < argc) {
            args.speed = std::stod(argv[++i]);
        } else if (arg == "--species" && i + 1 < argc) {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                args.species.push_back(argv[++i]);
            }
        } else if (arg == "--screen" && i + 1 < argc) {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                args.screens.push_back(argv[++i]);
            }
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            args.help = true;
        }
    }

    if (args.help) {
        std::cout << "Allowed options:\n"
                  << "  --help,-h           Shows this help message\n"
                  << "  --species <species> Species of pets to spawn (required)\n"
                  << "  --screen <screen>   Monitors the app will display on (part of the name)\n"
                  << "  --scale <value>     Scale multiplier\n"
                  << "  --speed <value>     Speed multiplier\n"
                  << "  --debug             Enable debug hud\n";
    }

    return args;
}