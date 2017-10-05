#include <stdio.h>
#include <assert.h>
#include "bst.h"

int main() {
    // create empty tree
    struct BstNode* root = NULL;

    // need to keep track of the first node inserted, using as ref to the root of the tree
    root = insert(root, 20);
    insert(root, 12);


    assert(search(root, 12)==true);

    return 0;
}