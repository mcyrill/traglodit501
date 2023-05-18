#include "iostream"

#include "argparse/Command.h"
#include "encoder/encoder.h"
#include "decoder/decoder.h"


int main(int argc, char *argv[]) {
    std::string filename;

    auto rootCmd = Command("", argc, argv);

    auto encodeCmd = Command("encode", [&filename]() {
        encode(filename);
    });
    encodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&encodeCmd);

    auto decodeCmd = Command("decode", [&filename]() {
        decode(filename);
    });
    decodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&decodeCmd);

    rootCmd.execute();

    return 0;
}