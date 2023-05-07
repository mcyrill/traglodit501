#include "HuffmanTree.h"
#include <queue>
#include <vector>


HuffmanTree::HuffmanTree() : root(nullptr) {};

void HuffmanTree::destroyTree(Node *node) {
    if (node != nullptr) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}

HuffmanTree::~HuffmanTree() {
    destroyTree(this->root);
}

std::map<char, int> HuffmanTree::getFrequencyTable(std::istream &is) {
    std::map<char, int> freqTable;
    char c;
    while (is >> c) {
        freqTable[c]++;
    }
    return freqTable;
}

void HuffmanTree::fillEncodingTable(Node* node, Bitset bitset) {
    if (node->isDeterment()) {
        this->encodingTable[node->getSymbol()] = bitset;
        return;
    }
    bitset.push_back(false);
    this->fillEncodingTable(node->getLeft(), bitset);
    bitset.pop_back();

    bitset.push_back(true);
    this->fillEncodingTable(node->getRight(), bitset);
}

std::map<char, Bitset> HuffmanTree::build(std::istream &is) {
    std::map<char, int> freqTable = this->getFrequencyTable(is);
    std::priority_queue<Node*, std::vector<Node*>, Comp> pq;
    for (auto s : freqTable) {
        pq.push(new Node(s.first, s.second));
    }

    while (pq.size() > 1) {
        auto node1 = pq.top();
        pq.pop();
        auto node2 = pq.top();
        pq.pop();
        auto newNode = new Node(' ', node1->getFrequency() + node2->getFrequency());
        pq.push(newNode);
    }
    this->root = pq.top();
    pq.pop();

    this->fillEncodingTable(this->root, Bitset());
    return this->encodingTable;
}