// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template <class T>
class BST {
 private:
    struct Node {
        T key;
        int cnt;
        Node* left;
        Node* right;

        explicit Node(T val) {
            key = val;
            cnt = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    void addNode(Node** cur, T val) {
        if (*cur == nullptr) {
            *cur = new Node(val);
            return;
        }

        if (val == (*cur)->key) {
            (*cur)->cnt++;
            return;
        }

        if (val < (*cur)->key) {
            addNode(&((*cur)->left), val);
        } else {
            addNode(&((*cur)->right), val);
        }
    }

    int findNode(Node* cur, T val) {
        if (cur == nullptr) {
            return 0;
        }

        if (cur->key == val) {
            return cur->cnt;
        }

        if (val < cur->key) {
            return findNode(cur->left, val);
        }

        return findNode(cur->right, val);
    }

    int calcDepth(Node* cur) {
        if (cur == nullptr) {
            return 0;
        }

        int l = calcDepth(cur->left);
        int r = calcDepth(cur->right);

        if (l > r) {
            return l + 1;
        }

        return r + 1;
    }

    void clearTree(Node* cur) {
        if (cur == nullptr) {
            return;
        }

        clearTree(cur->left);
        clearTree(cur->right);

        delete cur;
    }

    void fillVec(Node* cur,
        std::vector<std::pair<std::string, int>>* vec) {
        if (cur == nullptr) {
            return;
        }

        fillVec(cur->left, vec);

        vec->push_back(std::make_pair(cur->key, cur->cnt));

        fillVec(cur->right, vec);
    }

 public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clearTree(root);
    }

    void insert(T val) {
        addNode(&root, val);
    }

    int search(T val) {
    return findNode(root, val);
    }

    int depth() {
        return calcDepth(root) - 1;
    }

    void getWords(std::vector<std::pair<std::string, int>>* vec) {
        fillVec(root, vec);
    }
};

#endif  // INCLUDE_BST_H_
