//
// Created by josoder on 13.10.17.
//
//

/**
 * Sry about the sudden change in naming, just changed my name and decided to use a different typ of naming convention..
 * In particular, I will use capital letters in the beginning of function names.
 *
 * The red and black tree will also be of a generic type, which was not the case for the bst.
 */

#ifndef DATASTRUCTURES_RBBST_H
#define DATASTRUCTURES_RBBST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct rbt_node {
    void* key;
    void* value;
    bool red;
    bool isLeftChild;
    struct rbt_node* left;
    struct rbt_node* right;
    struct rbt_node* parent;
} rbt_node;

typedef struct rbt_tree {
    // since it is generic, client needs to implement functions to free, print and compare
    int (*Comparetor)(const void* a, const void* b);
    void (*PrintValue) (const void* value);
    void (*PrintKey) (const void* key);
    void (*DestroyVal) (const void* value);
    void (*DestroyKey) (const void* key);

    rbt_node* root;
} rbt_tree;

rbt_tree* CreateRBBST(int (*ComparetorFunc)(const void*, const void*),
                      void (*PrintValueFunc)(const void*),
                      void (*PrintKeyFunc)(const void*),
                      void (*DestroyKeyFunc)(const void*),
                      void (*DestroyValFunc)(const void*));

void RBTInsert(rbt_tree* tree, void* key, void* value);
void Insert(rbt_tree* tree ,rbt_node* parent, rbt_node* newNode);
void RBTPrint(rbt_tree* tree);
void RBTDelete(rbt_tree* tree, void* key);
void RBTDestroy(rbt_tree*);


#endif //DATASTRUCTURES_RBBST_H
