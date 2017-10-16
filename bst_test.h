//
// Created by josoder on 13.10.17.
//
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <assert.h>
#include <time.h>

void bst_test(){
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
    printf("%d\n", root->data);

    //     110
    //    /   \
    //   50   120
    //         /
    //        110

    assert(find_min(root->right)->data==120);
    assert(find_max(root)->data==120);

    // print the tree(in order), but lets add some random values first

    srand(time(NULL));

    for(int i=0; i<25; i++){
        insert(root, rand()%300);
    }

    print_tree(root);

    free_bst(root);
};
