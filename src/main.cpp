#include "argparse/Command.h"
#include "iostream"

using namespace std;


int main(int argc, char *argv[]) {
    std::string filename;

    auto rootCmd = Command("root", argc, argv);

    auto decode = Command("decode", [&filename]() {cout << filename;});
    decode.stringVar("file", "f", &filename);
    rootCmd.registerCommand(&decode);

    auto encode = Command("encode", [&filename]() {cout << filename;});
    rootCmd.registerCommand(&encode);

    rootCmd.execute();

    return 0;
}