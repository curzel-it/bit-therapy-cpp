#include "args.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(ArgsTests, CanParseHelp) {
    const char* argv[] = {"program", "--help"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    EXPECT_TRUE(args.help);
}

TEST(ArgsTests, CanParseDebug) {
    const char* argv[] = {"program", "--debug"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    EXPECT_TRUE(args.debug);
}

TEST(ArgsTests, CanParseScale) {
    const char* argv[] = {"program", "--scale", "1.5"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    EXPECT_DOUBLE_EQ(args.scale, 1.5);
}

TEST(ArgsTests, CanParseSpeed) {
    const char* argv[] = {"program", "--speed", "2.0"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    EXPECT_DOUBLE_EQ(args.speed, 2.0);
}

TEST(ArgsTests, CanParseSpecies) {
    const char* argv[] = {"program", "--species", "ape", "tiger"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    std::vector<std::string> expectedSpecies = {"ape", "tiger"};
    EXPECT_EQ(args.species, expectedSpecies);
}

TEST(ArgsTests, CanParseScreens) {
    const char* argv[] = {"program", "--screen", "HDMI1", "HDMI2"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    std::vector<std::string> expectedScreens = {"HDMI1", "HDMI2"};
    EXPECT_EQ(args.screens, expectedScreens);
}

TEST(ArgsTests, CanHandleUnknownArgument) {
    const char* argv[] = {"program", "--unknown"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    Arguments args = parseArgs(argc, const_cast<char**>(argv));
    EXPECT_TRUE(args.help); 
}