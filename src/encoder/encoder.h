#ifndef TRAGLODIT501_ENCODER_H
#define TRAGLODIT501_ENCODER_H

#include <string>
#include <fstream>
#include <ostream>
#include <istream>
#include <map>

#include "../exceptions/exceptions.h"
#include "HuffmanTree/HuffmanTree.h"
#include "../types.h"


void writeCompressedFile(
        const std::string& filename,
        const std::ifstream& is,
        const std::map<char, Bitset>& encodingTable);


void encode(const std::string& filename) {
    std::ifstream fis;
    fis.open(filename);
    if (!fis) {
        throw FileNotFoundException(filename);
    }
    auto tree = HuffmanTree();
    std::map<char, Bitset> encodingTable = tree.build(fis);

    writeCompressedFile(filename, fis, encodingTable);
}

#endif //TRAGLODIT501_ENCODER_H
