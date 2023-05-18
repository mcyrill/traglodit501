#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>

#include "encoder.h"
#include "../types.h"

std::size_t countBytesCntForEncodingTable(const std::map<char, Bitset> &encodingTable) {
    std::size_t cnt = encodingTable.size() * 2;
    for (const auto& s : encodingTable) {
        cnt += (s.second.size() + 7) / 8;
    }
    return cnt;
}

void writeCompressedFile(
        const std::string &filename,
        std::map<char, Bitset> &encodingTable) {

    std::ifstream is(filename);
    std::string archiveName = filename + ".traglodit501";
    std::ofstream os(archiveName, std::ios::binary);

    std::size_t sizeOfMetadata = 2 + filename.size() + countBytesCntForEncodingTable(encodingTable);
    byte* metadata = new byte[sizeOfMetadata];
    metadata[0] = (byte) filename.size();
    for (int i = 0; i < filename.size(); i++) {
        metadata[i + 1] = filename[i];
    }
    metadata[filename.size() + 1] = (byte) encodingTable.size();
    std::size_t currentInd = filename.size() + 2;
    for (const auto& s : encodingTable) {
        metadata[currentInd] = s.first;
        currentInd++;
        char bytesCnt = (char) ((s.second.size() + 7) / 8);
        metadata[currentInd] = bytesCnt;
        currentInd++;
        for (int i = 0; i < bytesCnt; i++) {
            byte currentByte = 0;
            for (int j = i * 8; j < std::max(i * 8 + 8, (int) s.second.size()); j++) {
                currentByte |= byte(1) << (j - i * 8);
            }
            metadata[currentInd] = currentByte;
            currentInd++;
        }
    }
    os.write(metadata, sizeOfMetadata);
    delete[] metadata;

    byte* chunk = new byte[CHUNK_SIZE];
    std::fill(chunk, chunk + CHUNK_SIZE, 0);
    std::size_t bitsCnt = 0;

    char c;
    while (is.get(c)) {
        std::vector<bool>& encodedSymbol = encodingTable[c];
        if (bitsCnt + encodedSymbol.size() > CHUNK_SIZE * 8) {
            byte* bitsInChunkNotFilled = new byte[1];
            bitsInChunkNotFilled[0] = (byte) (CHUNK_SIZE * 8 - bitsCnt);
            os.write(bitsInChunkNotFilled, 8);
            os.write(chunk, CHUNK_SIZE);
            std::fill(chunk, chunk + CHUNK_SIZE, 0);
            bitsCnt = 0;
        }
        for (std::size_t i = 0; i < encodedSymbol.size(); i++) {
            std::size_t byteNumber = bitsCnt / 8;
            std::size_t bitNumber = bitsCnt % 8;
            if (encodedSymbol[i]) {
                chunk[byteNumber] |= byte(1) << bitNumber;
            }
            bitsCnt++;
        }
    }
    byte* bitsInChunkNotFilled = new byte[1];
    bitsInChunkNotFilled[0] = (byte) (CHUNK_SIZE * 8 - bitsCnt);
    os.write(bitsInChunkNotFilled, 8);
    os.write(chunk, CHUNK_SIZE);
}

void encode(const std::string& filename) {
    std::ifstream fis(filename);
    if (!fis) {
        throw FileNotFoundException(filename);
    }
    auto tree = HuffmanTree();
    std::map<char, Bitset> encodingTable = tree.build(fis);

    writeCompressedFile(filename, encodingTable);
}