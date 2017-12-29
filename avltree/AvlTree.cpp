//
// Created by ivi on 12/27/2017.
//

#include <functional>
#include "AvlTree.h"


using namespace ::std;

AvlTree::Node::Node(const int k,Node* p) : key(k) , parent(p) {}

AvlTree::Node::Node(const int k, Node* p, Node *l, Node *r)
        : key(k), parent(p), left(l), right(r) {}


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
    if (root == nullptr){
        root = new Node(value, nullptr);
        root->balance = 0;
    }
    else
        root->insert(value);
}

void AvlTree::Node::insert(int value) {
    if (value == key)
        return;

    if (value < key) {
        if (left == nullptr){
            left = new Node(value, this);
            left->balance = 0;
            balance--;
        }
        else
            left->insert(value);
    }

    if (value > key) {
        if (right == nullptr){
            right = new Node(value, this);
            right->balance = 0;
            balance++;
        }
        else right->insert(value);
    }

    if(balance != 0)
        upin(this);
}

/********************************************************************
 * Remove
 *******************************************************************/
void AvlTree::remove(const int value) {
    if (root != nullptr) {
        //remove root
        if (root->key == value) {
            auto toDelete = root;
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            } else if (root->left == nullptr) {
                root = root->right;
                root->parent = nullptr;
            } else if (root->right == nullptr){
                root = root->left;
                root->parent = nullptr;
            }
            else {
                auto symSucc = findSymSucc(root);
                auto toDeleteNode = symSucc;
                root->right = root->right->remove(symSucc->key);
                toDeleteNode->left = nullptr;
                toDeleteNode->right = nullptr;
                root = new Node(symSucc->key, nullptr, root->left, root->right);
                delete toDeleteNode;
            }
            toDelete->left = nullptr;
            toDelete->right = nullptr;
            delete toDelete;
        } else //remove inner nodes or leaves
            root->remove(value);
    }
}

AvlTree::Node *AvlTree::Node::remove(const int value) {

    if (value < key) {
        if (left != nullptr) {
            auto toDelete = left;
            left = left->remove(value);
            left->parent = this;
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                toDelete->parent = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (value > key) {
        if (right != nullptr) {
            auto toDelete = right;
            right = right->remove(value);
            right->parent = this;
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                toDelete->parent = nullptr;
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

        return new Node(symSucc->key, parent,left, right->remove(symSucc->key));
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
 * balance and Rotate
 *******************************************************************/



void AvlTree::Node::rotateLeft(Node* p) {
    if(p == nullptr || p->parent == nullptr)
        return;

    Node* prev = p->parent;
    p->parent = prev->parent;
    p->balance--;

    //parent not root
    if(prev->parent != nullptr){

        if(prev->parent->right == prev){
            prev->parent->right = p;
        }
        else{
            prev->parent->left = p;
        }
    }
    prev->right = p->left;
    p->left = prev;
    prev->balance++;
    return ;
}

void AvlTree::Node::rotateRight(Node* p) {
    if(p == nullptr)
        return;

    if(p->parent == nullptr){
        //root?
        return;
    }

    Node* prev = p->parent;
    p->parent = prev->parent;
    p->balance++;

    //parent not root
    if(prev->parent != nullptr){

        if(prev->parent->right == prev){
            prev->parent->right = p;
        }
        else{
            prev->parent->left = p;
        }
    }
    prev->left = p->right;
    p->right = prev;
    prev->balance++;

    return;
}

void AvlTree::Node::rotateLeftRight(Node* p) {
    if(p == nullptr || p->parent == nullptr)
        return;

    //TODO: Implement this
    return ;
}

void AvlTree::Node::rotateRightLeft(Node* p) {
    if(p == nullptr || p->parent == nullptr)
        return;
    //TODO: Implement this
    return ;
}

int AvlTree::Node::upin(Node* p) {
    if(p->parent == nullptr){
        return p->balance;
    }

    if(p->balance == -1 && p->parent->balance ==-1){
        //Rotation nach rechts
        rotateRight(p);

    }else if(p->balance ==1 && p->parent->balance == -1){
        //Doppelrotation links-rechts
        rotateLeftRight(p);
    }
    else if(p->balance == 1 && p->parent->balance ==1){
        //Doppelrotation rechts-links
        rotateLeft(p);
    }
    else if(p->balance == -1 && p->parent->balance ==1){
        //Rotation nach links
        rotateRightLeft(p);
    }

    return 0;
}

bool AvlTree::isBalanced() {
    return false;
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



