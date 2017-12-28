//
// Created by ivi on 12/27/2017.
//

#include <functional>
#include "AvlTree.h"


using namespace ::std;

AvlTree::Node::Node(const int k) : key(k) {}

AvlTree::Node::Node(const int k, Node *l, Node *r)
        : key(k), left(l), right(r) {}


AvlTree::Node::~Node() {
    delete left;
    delete right;
}


AvlTree::~AvlTree() {
    delete root;
}

/********************************************************************
 * Search
 *******************************************************************/
bool AvlTree::search(const int value) const {

    if (root == nullptr)
        return false;

    return root->search(value);

}

bool AvlTree::Node::search(const int value) const {

    if (value == key) return true;

    if (value < key && left != nullptr) return left->search(value);

    if (value > key && right != nullptr) return right->search(value);

    return false;

}

/********************************************************************
 * Insert
 *******************************************************************/
void AvlTree::insert(const int value) {
    if (root == nullptr)
        root = new Node(value);
    else
        root->insert(value);
}

void AvlTree::Node::insert(int value) {
    if (value == key)
        return;

    if (value < key) {
        if (left == nullptr)
            left = new Node(value);
        else
            left->insert(value);
    }

    if (value > key) {
        if (right == nullptr)
            right = new Node(value);
        else right->insert(value);
    }
}

/********************************************************************
 * Remove
 *******************************************************************/
void AvlTree::remove(const int value) {
    if (root != nullptr) {
        if (root->key == value) {
            auto toDelete = root;
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            } else if (root->left == nullptr) {
                root = root->right;
            } else if (root->right == nullptr)
                root = root->left;
            else {
                auto symSucc = findSymSucc(root);
                auto toDeleteNode = symSucc;
                root->right = root->right->remove(symSucc->key);
                toDeleteNode->left = nullptr;
                toDeleteNode->right = nullptr;
                root = new Node(symSucc->key, root->left, root->right);
                delete toDeleteNode;
            }
            toDelete->left = nullptr;
            toDelete->right = nullptr;
            delete toDelete;
        } else
            root->remove(value);
    }
}

AvlTree::Node *AvlTree::Node::remove(const int value) {

    if (value < key) {
        if (left != nullptr) {
            auto toDelete = left;
            left = left->remove(value);
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (value > key) {
        if (right != nullptr) {
            auto toDelete = right;
            right = right->remove(value);
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (key == value) {
        if (left == nullptr && right == nullptr)
            return nullptr;
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        auto symSucc = findSymSucc(this);
        return new Node(symSucc->key, left, right->remove(symSucc->key));
    }
    // code should not be reached, just to make the compiler happy
    return nullptr;
}

AvlTree::Node *findSymSucc(AvlTree::Node * node) {
    if (node->right == nullptr)
        return nullptr;
    auto result = node->right;
    while (result->left != nullptr) {
        result = result->left;
    }
    return result;
}

/********************************************************************
 * Empty
 *******************************************************************/

/**
 * Returns true if this tree contains no elements.
 * @return true if this tree contains no elements
 */
bool AvlTree::isEmpty() {
    return (root== nullptr);
}



/********************************************************************
 * operator<<
 *******************************************************************/

std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;
                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;
                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;

    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }

    os << "}" << endl;

    return os;

}



