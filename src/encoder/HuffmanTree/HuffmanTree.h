#ifndef TRAGLODIT501_HUFFMANTREE_H
#define TRAGLODIT501_HUFFMANTREE_H

#include "istream"
#include <map>

#include "Node.h"
#include "../types.h"


class HuffmanTree {
private:
    Node *root;

    static std::map<char, int> getFrequencyTable(std::istream &is);

    void destroyTree(Node *node);

public:
    HuffmanTree();

    ~HuffmanTree();

    std::map<char, Bitset> build(std::istream &is);
};


#endif //TRAGLODIT501_HUFFMANTREE_H
