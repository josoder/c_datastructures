//
// Created by josoder on 05.10.17.
//
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>


BstNode* get_new_node(int data){
    BstNode* newNode= (BstNode*) malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


BstNode* insert(BstNode *root, int data){
    if (root == NULL){
        // base case this is where we insert
        root = get_new_node(data);
    }
    else if(root->data >= data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}

bool search(BstNode *root, int data){
    if(root == NULL) {
        return false;
    }
    else if(root->data == data) {
        return true;
    }
    else if(data <= root->data){
        return search(root->left, data);
    }
    else{
        return search(root->right, data);
    }

}

