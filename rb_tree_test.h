//
// Created by josoder on 13.10.17.
//

#ifndef DATASTRUCTURES_RB_TREE_TREST_H
#define DATASTRUCTURES_RB_TREE_TREST_H

#include <stdio.h>
#include "rbbst.h"

int CompareInt(const void* a, const void* b){
    if(a > b){
        return 1;
    }
    else if(a < b){
        return -1;
    }
    return 0;
}

void PrintInt(const void* a){
    printf("%i", a);
}


void rb_test() {
    rbt_tree *tree;
    tree = CreateRBBST(CompareInt, PrintInt, PrintInt, NULL, NULL);

    for(int i = 0; i<45; i++) {
        RBTInsert(tree, i, 0);
    }

    RBTInsert(tree, 2, 0);

    RBTPrint(tree);

    RBTDestroy(tree);
}

#endif //DATASTRUCTURES_RB_TREE_TREST_H
