// Copyright 2021 NNTU-CS
#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm>

template<typename T>
class BST {
private:
    struct Node {
        T word;
        int count;
        Node* left;
        Node* right;
        
        Node(const T& value) : word(value), count(1), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int nodeCount;
    
    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            nodeCount++;
            return new Node(value);
        }
        
        if (value < node->word) {
            node->left = insert(node->left, value);
        } else if (value > node->word) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }
    
    bool search(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        
        if (value < node->word) {
            return search(node->left, value);
        } else if (value > node->word) {
            return search(node->right, value);
        } else {
            return true;
        }
    }
    
    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(depth(node->left), depth(node->right));
    }
    
    void inorderToArray(Node* node, Pair*& arr, int& index) const {
        if (node == nullptr) {
            return;
        }
        
        inorderToArray(node->left, arr, index);
        arr[index++] = {node->word, node->count};
        inorderToArray(node->right, arr, index);
    }
    
    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    struct Pair {
        T word;
        int count;
    };
    
    BST() : root(nullptr), nodeCount(0) {}
    
    ~BST() {
        clear(root);
    }
    
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    bool search(const T& value) const {
        return search(root, value);
    }
    
    int depth() const {
        return depth(root);
    }
    
    int size() const {
        return nodeCount;
    }
    
    int getSortedArray(Pair*& arr) const {
        arr = new Pair[nodeCount];
        int index = 0;
        inorderToArray(root, arr, index);
        return nodeCount;
    }
};

#endif // INCLUDE_BST_H_
