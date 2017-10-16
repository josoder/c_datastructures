//
// Created by josoder on 13.10.17.
//
#include "../interfaces/rbbst.h"
#include "string.h"

// Util functions

void *MallocSafe(size_t size) {
    void *result;

    result = malloc(size);

    if (result != NULL) {
        return result;
    }

    printf("error: malloc failed");
    exit(-1);
}

/**
 * Create and return pointer to new node
 * @return
 */
rbt_node *CreateNewNode() {
    rbt_node *newNode = (rbt_node *) MallocSafe(sizeof(rbt_node));
    return newNode;
}

// Creation of the tree, allocate space etc..

/**
 * Create a red and black bst
 * @param ComparetorFunc
 * @param DestroyKeyFunc
 * @param DestroyValueFunc
 * @param PrintValueFunc
 * @param PrintKeyFunc
 * @return
 */
rbt_tree *CreateRBBST(int (*ComparetorFunc)(const void *, const void *),
                      void (*PrintValueFunc)(const void *),
                      void (*PrintKeyFunc)(const void *),
                      void (*DestroyKeyFunc)(const void *),
                      void (*DestroyValFunc)(const void *)) {
    rbt_tree *newTree;

    newTree = (rbt_tree *) MallocSafe(sizeof(rbt_tree));


    newTree->root = NULL;
    newTree->Comparetor = ComparetorFunc;
    newTree->PrintValue = PrintValueFunc;
    newTree->PrintKey = PrintKeyFunc;
    newTree->DestroyKey = DestroyKeyFunc;
    newTree->DestroyVal = DestroyValFunc;
}


// Methods for insertion

/**
 * Insert key-value pair
 * Firstly just as we would in a regular BST, except that the nodes now will have some extra properties.
 */
void RBTInsert(rbt_tree *tree, void *key, void *value) {
    if (tree->root == NULL) {
        tree->root = CreateNewNode();
        tree->root->key = key;
        tree->root->value = value;
        tree->root->red = false;
        return;
    }

    rbt_node *newNode = CreateNewNode();
    newNode->red = true;
    newNode->key = key;
    Insert(tree, tree->root, newNode);

    CheckColor(tree, newNode);
}

/**
 * Normal BST insert but nodes now have some additional information.
 */
void Insert(rbt_tree *tree, rbt_node *parent, rbt_node *newNode) {
    // replace parent with tmp if it is an update
    if (tree->Comparetor(parent->key, newNode->key) == 0) {
        if(parent->value != newNode->value){
            rbt_node* tmp = parent;
            parent = newNode;
            free(tmp);
        }
    }
    // If key is bigger than parents, recursively find its place in the right subtree
    if (tree->Comparetor(newNode->key, parent->key) > 0) {
        if (parent->right == NULL) {
            parent->right = newNode;
            newNode->isLeftChild = false;
            newNode->parent = parent;
            return;
        }
        return Insert(tree, parent->right, newNode);
    }
    // key is less so recursively find its place in the left subtree
    if (parent->left == NULL) {
        parent->left = newNode;
        newNode->isLeftChild = true;
        newNode->parent = parent;
        return;
    }
    return Insert(tree, parent->left, newNode);
}

// Methods for destroying the tree and all memory allocated

/**
 * Recursively free allocated memory from all nodes
 */
void DestroyNode(rbt_tree *tree, rbt_node *current) {
    if (current == NULL) {
        return;
    }

    if (current->left != NULL) {
        DestroyNode(tree, current->left);
    }

    if (current->right != NULL) {
        DestroyNode(tree, current->right);
    }

    // Use custom delete functions if present before freeing the node
    if (tree->DestroyVal != NULL) {
        tree->DestroyVal(current->value);
    }
    if (tree->DestroyKey != NULL) {
        tree->DestroyKey(current->key);
    }

    free(current);
}


/**
 * Destroy tree, free allocated memory
 */
void RBTDestroy(rbt_tree *tree) {
    DestroyNode(tree, tree->root);
}


// Methods to make sure its a valid red and black tree
// The rules:
// 1. root is always black,
// 2. no two consecutive red nodes,
// 3. same number of black nodes on every path from root to leaf.

void LeftRightRotate(rbt_tree *tree, rbt_node *grandParent) {
    LeftRotate(tree, grandParent->left);
    RightRotate(tree, grandParent->right);
}


void RightLeftRotate(rbt_tree *tree, rbt_node* grandParent) {
    // first right rotate parent
    RightRotate(tree, grandParent->right);
    // the problem is now reduced and we can fix it with a right rotate
    LeftRotate(tree, grandParent);
}

/**
 * Current is the the problem node(3),
 * 1                 p?
 *  \                  \
 *   2    ->           2
 *    \               / \
 *     3            1    3
 * we need to rotate so that parent(2) becomes the new parent of our subtree.
 * Current is the grand parent of the problem node(1).
 * @param tree
 * @param current
 */
void LeftRotate(rbt_tree *tree, rbt_node *grandParent) {
    rbt_node *tmp = grandParent->right;

    // if parent has a left child it will now become grandparent's right child
    grandParent->right = tmp->left;

    if (tmp->left != NULL) {
        tmp->left->parent = grandParent;
        // since it is now a right child..
        tmp->left->isLeftChild = false;
    }
    if (grandParent->parent == NULL) {
        // grandparent is root and the parent thus will become so
        tree->root = tmp;
        tmp->parent = NULL;
        tmp->red = false;
    }
    else {
        // We are not root, so we need to point tmp->parent to grandparent's
        tmp->parent = grandParent->parent;
        if (grandParent->isLeftChild) {
            tmp->isLeftChild = true;
            grandParent->parent->left = tmp;
        }
        else {
            tmp->isLeftChild = false;
            grandParent->parent->right = tmp;
        }
    }
    tmp->left = grandParent;
    grandParent->isLeftChild = true;
    grandParent->parent = tmp;
}

/**
 * See LeftRotate, same but mirrored.
 * @param tree
 * @param grandParent
 */
void RightRotate(rbt_tree *tree, rbt_node *grandParent) {
    rbt_node *tmp = grandParent->left;

    grandParent->left = tmp->right;

    if (tmp->right != NULL) {
        tmp->right->parent = grandParent;
        tmp->left->isLeftChild = true;
    }
    if (grandParent->parent == NULL) {
        tree->root = tmp;
        tmp->parent = NULL;
        tmp->red = false;
    }
    else {
        tmp->parent = grandParent->parent;
        if (grandParent->isLeftChild) {
            tmp->isLeftChild = true;
            grandParent->parent->left = tmp;
        }
        else {
            tmp->isLeftChild = false;
            grandParent->parent->right = tmp;
        }
    }
    tmp->right = grandParent;
    grandParent->isLeftChild = false;
    grandParent->parent = tmp;
}

/**
 * Rotate tree.
 * There are 4 different situations and solutions.
 * 1. right rotate(current node and parent is both left child and red), 2. left rotate(mirror of nr 1).
 * 3. left-right rotate (current node is right child and parent is left), 4. right-left(mirror of nr 3).
 * @param tree
 * @param current
 */
void Rotate(rbt_tree *tree, rbt_node *current) {
    // 1 or 3
    if (current->isLeftChild) {
        // 1, rotate right
        if (current->parent->isLeftChild) {
            RightRotate(tree, current->parent->parent);
            // Correct colors after rotation
            current->red = true;
            current->parent->red = false;
            if (current->parent->right != NULL) {
                current->parent->right->red = true;
            }
            return;
        }

        // 3, Right-left rotate
        RightLeftRotate(tree, current->parent->parent);
        current->red = false;
        current->parent->parent->red = true;
        current->parent->right = true;
        return;
    }
    // 2 or 4, current is right child

    // 2, left rotate
    if (current->parent->isLeftChild == false) {
        LeftRotate(tree, current->parent->parent);
        current->red = true;
        current->parent->red = false;
        if (current->parent->left != NULL) {
            current->parent->left->red = true;
        }
        return;
    }

    // 4, left-right rotate
    LeftRightRotate(tree, current);
    current->red = false;
    current->parent->red = true;
    if (current->parent->left != NULL) {
        current->parent->left = true;
    }
}

/**
 * Correct a violation.
 * If the aunt(parent->parent child node) of the current node is black, we will need to rotate, if its red we will flip
 * colors.
 * @param tree
 * @param current
 */
void CorrectTree(rbt_tree *tree, rbt_node *current) {
    // if parent is left child, the aunt has to be the right child.
    if (current->parent->isLeftChild) {
        // if aunt is black, we will need to rotate(NULL is treated as black).
        if (current->parent->parent->right == NULL || current->parent->parent->right->red == false) {
            return Rotate(tree, current);
        }
        // Aunt is red, flip colors.
        if (current->parent->parent->right != NULL) {
            current->parent->parent->right->red = false;
        }
        current->parent->red = false;
        current->parent->parent->red = true;
        return;
    }
    // parent is right child
    if (current->parent->parent->left == NULL || current->parent->parent->left->red == false) {
        return Rotate(tree, current);
    }
    if (current->parent->parent->left != NULL) {
        current->parent->parent->left->red = false;
    }
    current->parent->red = false;
    current->parent->parent->red = true;
    return;

}

/**
 * Check rule nr 2, recursively from the current node upwards to root.
 * @param tree
 * @param current
 */
void CheckColor(rbt_tree *tree, rbt_node *current) {
    // Cant be any violation above it
    if (current == tree->root) {
        return;
    }
    // Constraint nr 2, needs correction.
    if (current->red == true && current->parent->red == true) {
        CorrectTree(tree, current);
    }
    CheckColor(tree, current->parent);
    tree->root->red = false;
}

// Methods for printing the tree
void RBTPrint(rbt_tree *tree) {
    printf("{");
    PrintNode(tree, tree->root);
    printf("}\n");
}

/**
 * Recursively print all nodes in the tree in order.
 * @param tree
 * @param current
 */
void PrintNode(rbt_tree *tree, rbt_node *current) {
    if (current == NULL) {
        return;
    }

    if (current->left != NULL) {
        PrintNode(tree, current->left);
    }
    printf("[k:");
    tree->PrintKey(current->key);
    printf("v:");
    tree->PrintValue(current->value);
    printf("],");
    if (current->right != NULL) {
        PrintNode(tree, current->right);
    }
}

