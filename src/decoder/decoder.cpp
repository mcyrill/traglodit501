#include "decoder.h"
#include "../constants.h"


void decode(std::string& filename) {
    std::ifstream fis(filename, std::ios::binary);
    if (!fis) {
        throw FileNotFoundException(filename);
    }
    std::map<Bitset, char> decodingTable;
    std::string decodedFilename;
    byte filenameLength;
    if (!(fis >> filenameLength)) {
        throw CouldNotDecodeException(filename);
    }
    for (int i = 0; i < filenameLength; i++) {
        char c;
        if (!(fis >> c)) {
            throw CouldNotDecodeException(filename);
        }
        decodedFilename.push_back(c);
    }

    byte decodingTableSize;
    if (!(fis >> decodingTableSize)) {
        throw CouldNotDecodeException(filename);
    }
    for (int i = 0; i < decodingTableSize; i++) {
        char symbol;
        if (!(fis.get(symbol))) {
            throw CouldNotDecodeException(filename);
        }
        byte bitsCnt;
        if (!(fis.get(bitsCnt))) {
            throw CouldNotDecodeException(filename);
        }
        Bitset code;
        byte b[(bitsCnt + 7) / 8];
        fis.read(b, (bitsCnt + 7) / 8 * sizeof(byte));
        for (int j = 0; j < (bitsCnt + 7) / 8; j++) {
            for (int l = 0; l < std::min(8, bitsCnt - j * 8); l++) {
                if (b[j] & (1 << l)) {
                    code.push_back(true);
                } else {
                    code.push_back(false);
                }
            }
        }
        decodingTable[code] = symbol;
    }

    std::ofstream fos(decodedFilename);
    short bitsInChunk;
    byte chunk[CHUNK_SIZE];
    while (fis.peek() != std::ifstream::traits_type::eof()) {
        fis.read(reinterpret_cast<char*>(&bitsInChunk), sizeof(short));
        if (!fis) {
            throw CouldNotDecodeException(filename);
        }
        fis.read(chunk, CHUNK_SIZE);
        if (!fis) {
            throw CouldNotDecodeException(filename);
        }
        Bitset encodedSymbol;
        for (int i = 0; i < bitsInChunk; i++) {
            if (chunk[i / 8] >> (i % 8) & 1) {
                encodedSymbol.push_back(true);
            } else {
                encodedSymbol.push_back(false);
            }
            if (decodingTable.count(encodedSymbol)) {
                fos << decodingTable[encodedSymbol];
                encodedSymbol.clear();
            }
        }
        if (!encodedSymbol.empty()) {
            throw CouldNotDecodeException(filename);
        }
    }
}