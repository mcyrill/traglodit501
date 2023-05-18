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

const std::size_t CHUNK_SIZE = 512;


void writeCompressedFile(
        const std::string& filename,
        std::map<char, Bitset>& encodingTable);


void encode(const std::string& filename);

#endif //TRAGLODIT501_ENCODER_H
