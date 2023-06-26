#include <ostream>
#include <fstream>
#include "../constants.h"

#include "encoder.h"

std::size_t countBytesCntForEncodingTable(const std::unordered_map<char, Bitset> &encodingTable) {
    std::size_t cnt = encodingTable.size() * 2;
    for (const auto& s : encodingTable) {
        cnt += (s.second.size() + 7) / 8;
    }
    return cnt;
}

void writeEncodedFile(
        const std::string &filename,
        std::unordered_map<char, Bitset> &encodingTable) {

    std::ifstream is(filename, std::ios::binary);
    std::string archiveName = filename + ".traglodit501";
    std::ofstream os(archiveName, std::ios::binary);

    std::size_t sizeOfMetadata = 2 + filename.size() + countBytesCntForEncodingTable(encodingTable);
    byte* metadata = new byte[sizeOfMetadata];
    std::fill(metadata, metadata + sizeOfMetadata, 0);
    metadata[0] = (byte) filename.size();
    for (int i = 0; i < filename.size(); i++) {
        metadata[i + 1] = filename[i];
    }
    metadata[filename.size() + 1] = (byte) encodingTable.size();
    std::size_t currentInd = filename.size() + 2;
    for (const auto& s : encodingTable) {
        metadata[currentInd] = s.first;
        currentInd++;
        byte bitsCnt = (byte) s.second.size();
        metadata[currentInd] = bitsCnt;
        currentInd++;
        for (int i = 0; i < (bitsCnt + 7) / 8; i++) {
            byte currentByte = 0;
            for (int j = i * 8; j < std::min(i * 8 + 8, (int) bitsCnt); j++) {
                if (s.second[j]) {
                    currentByte |= byte(1) << (j - i * 8);
                }
            }
            metadata[currentInd] = currentByte;
            currentInd++;
        }
    }
    os.write(metadata, sizeOfMetadata);
    delete[] metadata;
    if (!os) {
        throw CouldNotEncodeException(filename);
    }

    byte chunk[CHUNK_SIZE];
    std::fill(chunk, chunk + CHUNK_SIZE, 0);
    short bitsCnt = 0;

    char c;
    while (is.get(c)) {
        std::vector<bool>& encodedSymbol = encodingTable[c];
        if (bitsCnt + encodedSymbol.size() > CHUNK_SIZE * 8) {
            os.write(reinterpret_cast<const char*>(&bitsCnt), sizeof(bitsCnt));
            if (!os) {
                throw CouldNotEncodeException(filename);
            }
            os.write(chunk, CHUNK_SIZE);
            if (!os) {
                throw CouldNotEncodeException(filename);
            }
            std::fill(chunk, chunk + CHUNK_SIZE, 0);
            bitsCnt = 0;
        }
        for (auto && i : encodedSymbol) {
            std::size_t byteNumber = bitsCnt / 8;
            std::size_t bitNumber = bitsCnt % 8;
            if (i) {
                chunk[byteNumber] |= byte(1) << bitNumber;
            }
            bitsCnt++;
        }
    }
    os.write(reinterpret_cast<const char*>(&bitsCnt), sizeof(short));
    if (!os) {
        throw CouldNotEncodeException(filename);
    }
    os.write(chunk, CHUNK_SIZE);
    if (!os) {
        throw CouldNotEncodeException(filename);
    }
}

void encode(const std::string& filename) {
    std::ifstream fis(filename, std::ios::binary);
    if (!fis) {
        throw FileNotFoundException(filename);
    }
    auto tree = HuffmanTree();
    std::unordered_map<char, Bitset> encodingTable = tree.build(fis);
    if (encodingTable.empty()) {
        throw EmptyFileException(filename);
    }

    writeEncodedFile(filename, encodingTable);
}