//
// Created by ivi on 12/27/2017.
//

#include "testAvlTree.h"


using namespace std;

// empty tree
TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_TRUE(b.isEmpty());
}

// insert and search
TEST(AvlTreeTest, One_Node) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
}

TEST(AvlTreeTest, Seven_Nodes_Insert_Remove) {
    AvlTree b;
    //4 3 6 7 2 1 8
    b.insert(4);
    b.insert(3);
    b.insert(6);
    b.insert(7);
    b.insert(2);
    b.insert(1);
    b.insert(8);
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_TRUE(b.search(3));
    EXPECT_TRUE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    b.remove(3);
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_TRUE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    b.remove(4);
    EXPECT_TRUE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_FALSE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));

    b.remove(1);
    EXPECT_FALSE(b.search(1));
    EXPECT_TRUE(b.search(2));
    EXPECT_FALSE(b.search(3));
    EXPECT_FALSE(b.search(4));
    EXPECT_TRUE(b.search(6));
    EXPECT_TRUE(b.search(7));
    EXPECT_TRUE(b.search(8));
    EXPECT_FALSE(b.isEmpty());
    b.remove(2);
    b.remove(6);
    b.remove(7);
    b.remove(8);
    EXPECT_TRUE(b.isEmpty());
}