#ifndef TRAGLODIT501_HUFFMANTREE_H
#define TRAGLODIT501_HUFFMANTREE_H

#include <istream>
#include <map>

#include "Node.h"
#include "../../types.h"


class HuffmanTree {
private:
    Node *root;
    std::unordered_map<char, Bitset> encodingTable;

    static std::unordered_map<char, int> getFrequencyTable(std::istream &is);

    void fillEncodingTable(Node* node, Bitset bitset);

    void destroyTree(Node *node);

public:
    HuffmanTree();

    ~HuffmanTree();

    std::unordered_map<char, Bitset> build(std::istream &is);
};


#endif //TRAGLODIT501_HUFFMANTREE_H
