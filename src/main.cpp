#include "argparse/Command.h"
#include "iostream"

using namespace std;

void run() {
    cout << 5;
}

int main(int argc, char *argv[]) {
    auto rootCmd = Command("root", argc, argv);

    std::string var;
    auto decode = Command("decode");
    decode.stringVar("file", "f", &var);
    rootCmd.registerCommand(&decode);

    std::string p;
    auto encode = Command("encode", [&p]() {cout << p;});
    decode.registerCommand(&encode);

    rootCmd.execute();

    return 0;
}