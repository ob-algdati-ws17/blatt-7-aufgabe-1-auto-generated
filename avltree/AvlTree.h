//
// Created by ivi on 12/27/2017.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>

using namespace std;

class AvlTree {

private:
    struct Node {
        const int key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(const int);
        Node(const int, Node *, Node *);
        ~Node();
        bool search(const int) const;
        void insert(const int);
        Node *remove(const int);
    };
    Node *root = nullptr;

public:
    ~AvlTree();
    bool isEmpty();
    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //AVLTREE_AVLTREE_H
