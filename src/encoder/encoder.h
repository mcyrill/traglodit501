#ifndef TRAGLODIT501_ENCODER_H
#define TRAGLODIT501_ENCODER_H

#include <string>
#include <fstream>
#include <map>

#include "../exceptions/exceptions.h"
#include "HuffmanTree/HuffmanTree.h"
#include "../types.h"


void encode(const std::string& filename) {
    std::fstream fis;
    fis.open(filename);
    if (!fis) {
        throw FileNotFoundException(filename);
    }
    auto tree = HuffmanTree();
    std::map<char, Bitset> encodingTable = tree.build(fis);
}

#endif //TRAGLODIT501_ENCODER_H
