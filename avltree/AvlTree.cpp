//
// Created by ivi on 12/27/2017.
//

#include <functional>
#include <limits>
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
                root->balance = root->right->balance + root->left->balance;
            }
            toDeleteRoot->left = nullptr;
            toDeleteRoot->right = nullptr;
            toDeleteRoot->parent = nullptr;
            delete toDeleteRoot;
        } else //remove inner nodes or leaves
            if(root->right->key == value){
                root->remove(value);
                if(root->parent != nullptr)
                    root = root->parent;

            }
            else if(root->left->key == value){
                root->remove(value);

                if(root->parent != nullptr)
                    root = root->parent;
            }
            else
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
                if(balance == 0 )
                    upout(this);
                if(balance == 2)
                    rotateLeft(this);
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
                if(balance == 0 )
                    upout(this);
                if(balance == -2)
                    rotateRight(this);
            }

        }
        return this;
    }

    if (key == value) {
        if (left == nullptr && right == nullptr){
            return nullptr;
        }
        if (left == nullptr){
            return right;
        }
        if (right == nullptr){
            return left;
        }

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
    if(p == nullptr )
        return;


    if(p->parent == nullptr){
        //root
        Node* r = p->right;

        if(r->left == nullptr)
            r->balance--;

        p->parent = r;
        p->right = r->left;
        r->left =p;
        r->parent = nullptr;

        //set balance p
        if(p->right == nullptr && p->left == nullptr)
            p->balance = 0;
        else
            p->balance = (p->right != nullptr)? 1: -1;

        return;
    }


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
    if(prev->right == nullptr && prev->left == nullptr)
        prev->balance = 0;
    else
        prev->balance = (prev->right != nullptr)? 1: -1;

}

void AvlTree::Node::rotateRight(Node* p) {
    if(p == nullptr)
        return;

    if(p->parent == nullptr){
        //root
        Node* l = p->left;

        if(l->right == nullptr)
            l->balance++;

        p->parent = l;
        p->left = l->right;
        l->right =p;

        l->parent = nullptr;
        //set balance p
        if(p->right == nullptr && p->left == nullptr)
            p->balance = 0;
        else
            p->balance = (p->right != nullptr)? 1: -1;

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
    if(prev->right == nullptr && prev->left == nullptr)
        prev->balance = 0;
    else
        prev->balance = (prev->right != nullptr)? 1: -1;


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

int AvlTree::Node::getBalance(const int value) const {
    int result = std::numeric_limits<int>::max();
    if (value < key) {
        if (left != nullptr) {
            result = left->getBalance(value);
        }
        return result;
    }

    if (value > key) {
        if (right != nullptr) {
            result = right->getBalance(value);
        }
        return result;
    }

    if (key == value) {
        return balance;
    }
    // code should not be reached, just to make the compiler happy
    return result;
}

int AvlTree::getBalance(const int value) const {
    if(root == nullptr)
        return std::numeric_limits<int>::max();
    return root->getBalance(value);
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
    else if(p->parent->left == p){

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
    if( balance< -1 || balance > 1)
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
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
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




