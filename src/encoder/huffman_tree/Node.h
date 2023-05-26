#include <utility>

#ifndef TRAGLODIT501_NODE_H
#define TRAGLODIT501_NODE_H


class Node {
private:
    char s;
    int frequency;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
public:
    Node(char s, int frequency) : s(s), frequency(frequency), left(nullptr), right(nullptr) {};
    ~Node() = default;

    bool isDeterment() const { return this->left == nullptr && this->right == nullptr; }

    char getSymbol() const { return this->s; }

    std::shared_ptr<Node> getLeft() const { return this->left; }
    std::shared_ptr<Node> getRight() const { return this->right; }

    void setLeft(std::shared_ptr<Node> node) { this->left = std::move(node); }
    void setRight(std::shared_ptr<Node> node) {this->right = std::move(node); }

    int getFrequency() const { return this->frequency; }
};

struct Comp {
    bool operator()(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2){
        return node1->getFrequency() > node2->getFrequency();
    }
};

#endif //TRAGLODIT501_NODE_H
