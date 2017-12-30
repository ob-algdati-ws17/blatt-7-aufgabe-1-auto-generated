//
// Created by ivi on 12/27/2017.
//

#include "testAvlTree.h"


using namespace std;

// empty tree
TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_TRUE(b.isEmpty());
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());

    //check if tree is BST
    EXPECT_TRUE(b.isBST());
    //check if tree is balanced
    EXPECT_TRUE(b.isBalanced());

    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());

}

// insert and search
TEST(AvlTreeTest, One_Node) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));

    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));

    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(12213), 0);

    //check if tree is BST
    EXPECT_TRUE(b.isBST());
    //check if tree is balanced
    EXPECT_TRUE(b.isBalanced());
}

TEST(AvlTreeTest, Insert_Balance) {
    AvlTree b;

    //root
    b.insert(4);
    b.insert(3);
    EXPECT_EQ(b.getBalance(3), 0);
    EXPECT_EQ(b.getBalance(4), -1);
    b.insert(6);
    EXPECT_EQ(b.getBalance(3), 0);
    EXPECT_EQ(b.getBalance(6), 0);
    EXPECT_EQ(b.getBalance(4), 0);
    b.insert(7);
    EXPECT_EQ(b.getBalance(7), 0);
    EXPECT_EQ(b.getBalance(6), 1);
    EXPECT_EQ(b.getBalance(3), 0);
    EXPECT_EQ(b.getBalance(4), 0);

    b.insert(2);
    EXPECT_EQ(b.getBalance(4), 0);
    EXPECT_EQ(b.getBalance(7), 0);
    EXPECT_EQ(b.getBalance(6), 1);
    EXPECT_EQ(b.getBalance(2), 0);
    EXPECT_EQ(b.getBalance(3), -1);

    b.insert(1);
    EXPECT_EQ(b.getBalance(4), 0);
    EXPECT_EQ(b.getBalance(7), 0);
    EXPECT_EQ(b.getBalance(6), 1);

    EXPECT_EQ(b.getBalance(2), 0);
    EXPECT_EQ(b.getBalance(3), 0);
    EXPECT_EQ(b.getBalance(1), 0);

    b.insert(8);
    EXPECT_EQ(b.getBalance(4), 0);
    EXPECT_EQ(b.getBalance(7), 0);
    EXPECT_EQ(b.getBalance(6), 0);
    EXPECT_EQ(b.getBalance(8), 0);

    EXPECT_EQ(b.getBalance(2), 0);
    EXPECT_EQ(b.getBalance(3), 0);
    EXPECT_EQ(b.getBalance(1), 0);
}

TEST(AvlTreeTest, Remove_Balance){
    AvlTree b;
    //4 3 6 7 2 1 8
    b.insert(4);
    b.insert(3);
    b.insert(6);
    b.insert(7);
    b.insert(2);
    b.insert(1);
    b.insert(8);

    b.remove(3);
    //node removed doesn't exsist
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());

    EXPECT_EQ(b.getBalance(4), 0);
    EXPECT_EQ(b.getBalance(7), 0);
    EXPECT_EQ(b.getBalance(6), 0);
    EXPECT_EQ(b.getBalance(8), 0);
    EXPECT_EQ(b.getBalance(2), -1);
    EXPECT_EQ(b.getBalance(1), 0);
    b.remove(4);
    //nodes removed
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());

    EXPECT_EQ(b.getBalance(7), 1);
    EXPECT_EQ(b.getBalance(6), 0);
    EXPECT_EQ(b.getBalance(8), 0);
    EXPECT_EQ(b.getBalance(2), -1);
    EXPECT_EQ(b.getBalance(1), 0);

    b.remove(1);
    //nodes removed
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(1), std::numeric_limits<int>::max());

    EXPECT_EQ(b.getBalance(7), 1);
    EXPECT_EQ(b.getBalance(6), 1);
    EXPECT_EQ(b.getBalance(8), 0);
    EXPECT_EQ(b.getBalance(2), 0);

    b.remove(2);
    //nodes removed
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(1), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(2), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(7), 0);//root
    EXPECT_EQ(b.getBalance(6), 0);
    EXPECT_EQ(b.getBalance(8), 0);


    b.remove(6);
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(1), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(2), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(6), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(7), 1);//root
    EXPECT_EQ(b.getBalance(8), 0);

    b.remove(7);

    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(1), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(2), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(6), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(7), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(8), 0);//new root


    b.remove(8);
    EXPECT_EQ(b.getBalance(3), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(4), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(1), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(2), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(6), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(7), std::numeric_limits<int>::max());
    EXPECT_EQ(b.getBalance(8), std::numeric_limits<int>::max());//new root

}

TEST(AvlTreeTest, Two_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

TEST(AvlTreeTest, Three_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
}

TEST(AvlTreeTest, Three_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
    b.remove(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

//insert some nodes and delete them and check all the time if the tree is still a BST and balanced
TEST(AvlTreeTest, Seven_Nodes_Insert_Remove_Balanced_BST) {
    AvlTree b;
    //4 3 6 7 2 1 8
    b.insert(4);
    b.insert(3);
    b.insert(6);
    b.insert(7);
    b.insert(2);
    b.insert(1);
    b.insert(8);

    EXPECT_THAT(*b.preorder(), testing::ElementsAre(4, 2, 1, 3, 7, 6, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(1, 2, 3,4,6,7,8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(1, 3, 2, 6, 8, 7, 4));
    //check if tree is BST
    EXPECT_TRUE(b.isBST());
    //check if tree is balanced
    EXPECT_TRUE(b.isBalanced());
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_TRUE(b.search(3));
    EXPECT_TRUE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    b.remove(3);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(4, 2, 1, 7, 6, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(1, 2, 4,6,7,8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(1, 2, 6, 8, 7, 4));

    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_TRUE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));

    //remove root
    b.remove(4);

    EXPECT_THAT(*b.preorder(), testing::ElementsAre(6, 2, 1, 7, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(1, 2, 6, 7, 8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(1, 2, 8, 7, 6));


    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_FALSE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    b.remove(1);

    EXPECT_THAT(*b.preorder(), testing::ElementsAre(6, 2, 7, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(2, 6, 7, 8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(2, 8, 7, 6));


    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    EXPECT_FALSE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_FALSE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    EXPECT_FALSE(b.isEmpty());
    b.remove(2);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre( 7, 6, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(6, 7, 8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre( 6, 8, 7));

    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    b.remove(6);

    EXPECT_THAT(*b.preorder(), testing::ElementsAre( 7, 8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre( 7, 8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre( 8, 7));

    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    b.remove(7);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(  8));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre( 8));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre( 8));


    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    b.remove(8);
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());

    EXPECT_TRUE(b.isBST());
    EXPECT_TRUE(b.isBalanced());
    EXPECT_TRUE(b.isEmpty());
}
