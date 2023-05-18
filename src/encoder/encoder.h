#ifndef TRAGLODIT501_ENCODER_H
#define TRAGLODIT501_ENCODER_H

#include <string>
#include <fstream>
#include <ostream>
#include <istream>
#include <map>

#include "../exceptions/exceptions.h"
#include "../huffman_tree/HuffmanTree.h"
#include "../types.h"


void writeEncodedFile(
        const std::string& filename,
        std::map<char, Bitset>& encodingTable);


void encode(const std::string& filename);

#endif //TRAGLODIT501_ENCODER_H
