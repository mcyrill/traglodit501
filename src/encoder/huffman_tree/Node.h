#ifndef TRAGLODIT501_NODE_H
#define TRAGLODIT501_NODE_H


class Node {
private:
    char s;
    int frequency;
    Node *left;
    Node *right;
public:
    Node(char s, int frequency) : s(s), frequency(frequency), left(nullptr), right(nullptr) {};
    ~Node() = default;

    bool isDeterment() const { return this->left == nullptr && this->right == nullptr; }

    char getSymbol() const { return this->s; }

    Node* getLeft() const { return this->left; }
    Node* getRight() const { return this->right; }

    void setLeft(Node* node) { this->left = node; }
    void setRight(Node* node) {this->right = node; }

    int getFrequency() const { return this->frequency; }
};

struct Comp {
    bool operator()(const Node* node1, const Node* node2){
        return node1->getFrequency() > node2->getFrequency();
    }
};

#endif //TRAGLODIT501_NODE_H
