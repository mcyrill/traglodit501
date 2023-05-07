#include "iostream"

#include "argparse/Command.h"
#include "encoder/encoder.h"


int main(int argc, char *argv[]) {
    std::string filename;

    auto rootCmd = Command("", argc, argv);

    auto encodeCmd = Command("encode", [&filename]() {
        encode(filename);
    });
    encodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&encodeCmd);

    auto decodeCmd = Command("decodeCmd", [&filename]() {std::cout << filename;});
    decodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&decodeCmd);

    rootCmd.execute();

    return 0;
}