#include "iostream"

#include "argparse/Command.h"
#include "encoder/encoder.h"
#include "decoder/decoder.h"


int main(int argc, char *argv[]) {
    std::string filename;

    Command rootCmd("", argc, argv);

    Command encodeCmd("encode", [&filename]() {
        encode(filename);
    });
    encodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(encodeCmd);

    Command decodeCmd("decode", [&filename]() {
        decode(filename);
    });
    decodeCmd.stringVar("file", "f", &filename);
    rootCmd.registerCommand(decodeCmd);

    rootCmd.execute();

    return 0;
}