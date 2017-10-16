//
// Created by josoder on 05.10.17.
//

#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

void free_bst(BstNode *root);

BstNode* find_max(BstNode *root);

BstNode* find_min(BstNode *root);

BstNode* delete(BstNode *root, int data);

bool search(BstNode *root, int data);

BstNode* get_new_node(int data);

BstNode* insert(BstNode *root, int data);

void print_tree(BstNode *root);

#endif //DATASTRUCTURES_BST_H
