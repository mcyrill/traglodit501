#include "HuffmanTree.h"
#include <memory>
#include <queue>
#include <vector>

std::unordered_map<char, int> HuffmanTree::getFrequencyTable(std::istream &is) {
    std::unordered_map<char, int> freqTable;
    char c;
    while (is.get(c)) {
        freqTable[c]++;
    }
    return freqTable;
}

void HuffmanTree::fillEncodingTable(std::shared_ptr<Node> node, Bitset bitset) {
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

std::unordered_map<char, Bitset> HuffmanTree::build(std::istream &is) {
    std::unordered_map<char, int> freqTable = this->getFrequencyTable(is);
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Comp> pq;
    for (auto s : freqTable) {
        pq.push(std::make_shared<Node>(s.first, s.second));
    }
    if (pq.empty()) {
        return this->encodingTable;
    }

    while (pq.size() > 1) {
        auto node1 = pq.top();
        pq.pop();
        auto node2 = pq.top();
        pq.pop();
        auto newNode = std::make_shared<Node>(' ', node1->getFrequency() + node2->getFrequency());
        newNode->setLeft(node1);
        newNode->setRight(node2);
        pq.push(newNode);
    }
    this->root = pq.top();
    pq.pop();

    this->fillEncodingTable(this->root, Bitset());
    return this->encodingTable;
}