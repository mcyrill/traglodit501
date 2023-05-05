#include "iostream"

#include "argparse/Command.h"


int main(int argc, char *argv[]) {
    std::string filename;

    auto rootCmd = Command("root", argc, argv);

    auto decode = Command("decode", [&filename]() {std::cout << filename;});
    decode.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&decode);

    auto encode = Command("encode", [&filename]() {std::cout << filename;});
    encode.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&encode);

    rootCmd.execute();

    return 0;
}