//
// Created by josoder on 05.10.17.
//

#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

#include <stdbool.h>

typedef struct {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

void free_bst(BstNode *root);

BstNode* find_min(BstNode *root);

BstNode* delete(BstNode *root, int data);

bool search(BstNode *root, int data);

BstNode* get_new_node(int data);

BstNode* insert(BstNode *root, int data);

#endif //DATASTRUCTURES_BST_H
