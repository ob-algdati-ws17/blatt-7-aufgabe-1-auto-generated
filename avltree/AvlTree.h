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
        Node *parent = nullptr;
        int balance;
        Node(const int, Node *);
        Node(const int, Node *, Node *, Node *);
        ~Node();
        bool search(const int) const;
        void insert(const int);
        Node *remove(const int);

        int upin(AvlTree::Node* p);
        int upout(AvlTree::Node* p);
        void rotateLeft(Node * p);
        void rotateRight(Node * p);
        void rotateLeftRight(Node * p);
        void rotateRightLeft(Node * p);

    };
    Node *root = nullptr;

public:
    ~AvlTree();
    bool isEmpty();
    bool isBalanced();

    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);


};

#endif //AVLTREE_AVLTREE_H
