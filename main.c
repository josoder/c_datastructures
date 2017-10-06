#include <stdio.h>
#include <assert.h>
#include "bst.h"

int main() {
    // create empty tree
    BstNode* root = NULL;

    // need to keep track of the first node inserted, using as ref to the root of the tree
    root = insert(root, 100);
    insert(root, 120);
    insert(root, 50);
    insert(root, 110);

    //     100
    //    /   \
    //   50   120
    //          \
    //          110

    assert(search(root, 120)==true);
    assert(search(root, 100)==true);
    assert(search(root, 110)==true);
    assert(search(root, 50)==true);
    assert(find_min(root)->data == 50);
    delete(root, 100);
    printf("%d", root->data);

    //     110
    //    /   \
    //   50   120
    //         /
    //        110

    assert(find_min(root->right)->data==120);
    free_bst(root);
    return 0;
}