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

/**
 * Insert data into tree
 * @param root
 * @param data
 * @return
 */
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

/**
 * Free allocated memory
 * @param root
 */
void free_bst(BstNode* root){
    // tree is empty
    if(root == NULL) {
        return;
    }

    free_bst(root->left);
    free_bst(root->right);

    free(root);
    root = NULL;
}

/**
 * Delete node which contains "data"
 * @param root
 * @param data
 * @return
 */
BstNode* delete(BstNode *root, int data){
    // tree is empty
    if(root == NULL) {
        return root;
    }
    else if(data < root->data) {
        root->left = delete(root->left, data);
    }
    else if(data > root->data) {
        root->right = delete(root->right, data);
    }
    else {
        // case 1: no child, no problem :)
        if(root->left == NULL && root->right == NULL){
            // free allocated memory, set root to NULL.
            free(root);
            root = NULL;
        }
            // case 2, node has one child node
        else if(root->left == NULL){
            // assign root to its right child node, and free the allocated memory
            BstNode *tmp = root;
            root = root->right;
            free(tmp);
        }
        else if(root->right == NULL){
            BstNode *tmp = root;
            root = root->left;
            free(tmp);
        }
            // case 3, node has two child nodes
        else {
            BstNode *tmp = find_min(root->right);
            root-> data = tmp->data;
            root->right = delete(root->right, tmp->data);
        }
    }
    return root;
}

/**
 * Recursively search for the biggest node in the right subtree
 * @param root
 * @return
 */
BstNode* find_max(BstNode* root){
    BstNode *tmp = root;

    if(tmp == NULL) {
        return root;
    }
    else if(root->right!=NULL){
        tmp = find_max(root->right);
    }
    // if there is not a node to the right we found max
    return tmp;
}

/**
 * Recursively search for the smalles node in the left subtree
 * @param root
 * @return
 */
BstNode* find_min(BstNode* root){
    BstNode *tmp = root;

    if(tmp == NULL){
        return root;
    }
    else if(root->left!=NULL){
        tmp = find_min(root->left);
    }

    return tmp;
}

/**
 * Recursively search the tree for the node with "data"
 * @param root
 * @param data
 * @return
 */
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

/**
 * Print the tree in order.
 * @param root
 */
void print_tree(BstNode* root){
    BstNode* tmp = root;

    if(tmp == NULL) {
        return;
    }

    if(tmp->left != NULL){
        print_tree(tmp->left);
    }

    printf("%d ", tmp->data);

    if(tmp->right != NULL){
        print_tree(tmp->right);
    }
}

