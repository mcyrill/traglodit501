#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>

#include "encoder.h"
#include "../types.h"

std::size_t countNeededBytesEncodingTable(const std::map<char, Bitset> &encodingTable) {
    std::size_t cnt = encodingTable.size() * 2;
    for (const auto& s : encodingTable) {
        cnt += (s.second.size() + 7) / 8;
    }
    return cnt;
}

void writeCompressedFile(
        const std::string &filename,
        const std::ifstream &is,
        const std::map<char, Bitset> &encodingTable) {

    std::string archiveName = filename + ".traglodit501";
    std::ofstream os(archiveName, std::ios::binary);

    byte* metadata = new byte[2 + filename.size() + countNeededBytesEncodingTable(encodingTable)];
    metadata[0] = (byte) filename.size();
    for (int i = 0; i < filename.size(); i++) {
        metadata[i + 1] = filename[i];
    }
    metadata[filename.size() + 1] = (char) encodingTable.size();
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
                currentByte += byte(1) << (j - i * 8);
            }
            metadata[currentInd] = currentByte;
            currentInd++;
        }
    }
    os.write(metadata, sizeof(metadata));
    delete[] metadata;

}