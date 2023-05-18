#include "decoder.h"


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
//    std::ofstream fos(decodedFilename);

    byte decodingTableSize;
    if (!(fis >> decodingTableSize)) {
        throw CouldNotDecodeException(filename);
    }
    for (int i = 0; i < decodingTableSize; i++) {
        char symbol;
        if (!(fis >> symbol)) {
            throw CouldNotDecodeException(filename);
        }
        byte bitsCnt;
        if (!(fis >> bitsCnt)) {
            throw CouldNotDecodeException(filename);
        }
        Bitset code;
        std::size_t bitsRead = 0;
        for (int j = 0; j < (bitsCnt + 7) / 8; j++) {
            byte b;
            if (!(fis >> b)) {
                throw CouldNotDecodeException(filename);
            }
            for (int l = 0; l < std::min(8, bitsCnt - j * 8); l++) {
                if (b & (1 << l)) {
                    code.push_back(true);
                } else {
                    code.push_back(false);
                }
            }
        }
        decodingTable[code] = symbol;
    }
}