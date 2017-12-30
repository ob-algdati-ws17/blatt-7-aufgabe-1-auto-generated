//
// Created by ivi on 12/27/2017.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <vector>

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

        int getBalance(const int) const;

        vector<int> *preorder() const; // (Hauptreihenfolge)
        vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)

    };
    Node *root = nullptr;
    bool isBST(AvlTree::Node* base, AvlTree::Node* left, AvlTree::Node * right);
    bool isBalanced(AvlTree::Node* base, int* height);

public:
    ~AvlTree();
    bool isEmpty();
    bool isBalanced();
    bool isBST();

    int getBalance(const int) const;

    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);

    vector<int> *preorder() const; // (Hauptreihenfolge)
    vector<int> *inorder() const; // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

};

#endif //AVLTREE_AVLTREE_H
