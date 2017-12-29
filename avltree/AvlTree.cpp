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

    return root != nullptr && root->search(value);

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
            auto toDeleteRoot = root;
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
                root = new Node(symSucc->key, nullptr, root->left, nullptr);
                root->right = toDeleteRoot->right->remove(symSucc->key);
                root->right->parent = root;
                root->left->parent = root;
            }
            toDeleteRoot->left = nullptr;
            toDeleteRoot->right = nullptr;
            toDeleteRoot->parent = nullptr;
            delete toDeleteRoot;
        } else //remove inner nodes or leaves
            root->remove(value);
    }
}

AvlTree::Node *AvlTree::Node::remove(const int value) {

    if (value < key) {
        if (left != nullptr) {
            auto toDelete = left;

            left = left->remove(value);

            if (toDelete->key == value) {
                balance++;
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                toDelete->parent = nullptr;
                delete toDelete;

                //check balance
                if(balance == 0)
                    upout(this);
            }

        }
        return this;
    }

    if (value > key) {
        if (right != nullptr) {
            auto toDelete = right;
            right = right->remove(value);

            if (toDelete->key == value) {
                balance--;
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                toDelete->parent = nullptr;
                delete toDelete;

                //check balance
                if(balance == 0)
                    upout(this);
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

}

void AvlTree::Node::rotateLeftRight(Node* p) {
    if(p == nullptr || p->parent == nullptr)
        return;

    rotateRight(p);
    rotateLeft(p->parent);
}

void AvlTree::Node::rotateRightLeft(Node* p) {
    if(p == nullptr || p->parent == nullptr)
        return;

    rotateLeft(p);
    rotateRight(p->parent);
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

int AvlTree::Node::upout(Node* p) {
    if(p->parent == nullptr){
        return p->balance;
    }

    if(p->parent->right == p){
        switch(p->parent->balance){
            case -1: //Fall 1.1
                p->parent->balance--;
                upout(p->parent);
                break;
            case 0:  //Fall 1.2
                p->parent->balance--;
                break;
            case 1:  //Fall 1.3
                p->parent->balance--;
                switch (p->parent->right->balance){
                    case 0:
                        rotateRight(p->parent);
                        upout(p->parent->parent);
                        break;
                    case 1:
                        rotateLeftRight(p->parent);
                        upout(p->parent->parent);
                        break;
                    case -1:
                        rotateRight(p->parent);
                        break;
                }
                break;
        }
    }
    else{

        switch(p->parent->balance){
            case -1: //Fall 1.1
                p->parent->balance++;
                upout(p->parent);
                break;
            case 0:  //Fall 1.2
                p->parent->balance++;
                break;
            case 1:  //Fall 1.3

                p->parent->balance++;
                switch (p->parent->right->balance){
                    case 0:
                        rotateLeft(p->parent);
                        break;
                    case 1:
                        rotateLeft(p->parent);
                        upout(p->parent->parent);
                        break;
                    case -1:
                        rotateRightLeft(p->parent);
                        upout(p->parent->parent);
                        break;
                }
                break;
        }

    };


    return 0;
}


bool AvlTree::isBalanced(AvlTree::Node* base, int* height) {

    if(root == nullptr){
        (*height) = 0;
        return true;
    }

    if(base == nullptr){
        return true;
    }

    int leftHeight = 0;
    int rightHeight = 0;
    bool isBalancedLeft = false;
    bool isBalancedRight= false;

    isBalancedLeft = isBalanced(base->left, &leftHeight);
    isBalancedRight = isBalanced(base->right, &rightHeight);

    *height = (leftHeight > rightHeight? leftHeight: rightHeight)+1;

    int balance = rightHeight  - leftHeight;
    if( balance< -1 && balance > 1)
        return false;

    return isBalancedLeft && isBalancedRight;
}

bool AvlTree::isBalanced() {

    //check everything xD

    int height = 0;

    return  isBalanced(root, &height) ;
}

bool AvlTree::isBST(AvlTree::Node* base, AvlTree::Node* left, AvlTree::Node * right) {
    if(base == nullptr)
        return true;

    if(left != nullptr && base->key < left->key)
        return false;

    if(right != nullptr && base->key > right->key)
        return false;

    if(base->left == nullptr && base->right == nullptr)
        return true;

    if(base->left != nullptr && base->right != nullptr)
        return isBST(base->left, base->left->left,base->left->right) && isBST(base->right, base->right->left,base->right->right);
    if(base->left == nullptr)
        return isBST(base->right, base->right->left,base->right->right);
    if(base->right == nullptr)
        return isBST(base->left, base->left->left,base->left->right);
}

bool AvlTree::isBST() {
    if(root == NULL)
        return true;

    return isBST(root, root->left, root->right);
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



