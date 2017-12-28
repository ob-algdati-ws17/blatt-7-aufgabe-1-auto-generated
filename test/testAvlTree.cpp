//
// Created by ivi on 12/27/2017.
//

#include "testAvlTree.h"


using namespace std;

// empty tree

TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_TRUE(b.isEmpty());
    //EXPECT_EQ(nullptr, b.preorder());
    //EXPECT_EQ(nullptr, b.inorder());
    //EXPECT_EQ(nullptr, b.postorder());
}