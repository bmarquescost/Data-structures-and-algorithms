#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

#define _max(a,b) (a >= b ? a : b)

struct _node {
    NODE *left;
    NODE *right;
    ELEMENT *element;
    int bf;
};

struct _avl {
    NODE *root;
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(1 * sizeof(NODE));
    new_node->element = e;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

AVL *avl_create(void) {
	AVL *tree = malloc(1 * sizeof(AVL));
	
	if(tree != NULL) 
        tree->root = NULL;
	
	return tree;
}

static int _avl_get_height(NODE *root) {
    if (root == NULL) return -1;

    int left_height = _avl_get_height(root->left) + 1;
    int right_height = _avl_get_height(root->right) + 1;

    return _max(left_height, right_height);
}

static int _node_get_balance_factor(NODE *curr) {
    int left_height = _avl_get_height(curr->left);
    int right_height = _avl_get_height(curr->right);

    return left_height - right_height;
}

static NODE *_right_rotate(NODE *root) {
    NODE *new_root = root->left;
    NODE *right_sub_tree = new_root->right;

    new_root->right = root;
    root->left = right_sub_tree;

    return new_root;
}

static NODE *_left_rotate(NODE *root) {
    NODE *new_root = root->right;
    NODE *left_sub_tree = new_root->left;

    new_root->left = root;
    root->right = left_sub_tree;

    return new_root;
}

static NODE *_left_right_rotate(NODE *root) {
    root->left = _left_rotate(root->left);
    return _right_rotate(root);
}

static NODE *_right_left_rotate(NODE *root) {
    root->right = _right_rotate(root->right);
    return _left_rotate(root);
}

static NODE *_avl_balance(NODE *curr, ELEMENT *e, int balancing) {
    if (balancing > 1 && element_get_value(e) < element_get_value(curr->left->element)) 
        return _right_rotate(curr); // rotate to the right

    else if (balancing < -1 && element_get_value(e) > element_get_value(curr->left->element))
        return _left_rotate(curr); // rotate to the left
    
    else if (balancing > 1 && element_get_value(e) > element_get_value(curr->left->element)) 
        return _left_right_rotate(curr); // rotate left then right
        
    else if(balancing < -1 && element_get_value(e) < element_get_value(curr->left->element))
        return _right_left_rotate(curr); // rotate right then left

    // Otherwise, tree is balanced 
    return curr; 
}

static NODE * _avl_insert(NODE *curr, ELEMENT *e) {
    if (curr == NULL)
        return _node_create(e);

    if (element_get_value(e) < element_get_value(curr->element))
        curr->left = _avl_insert(curr->left, e);
    
    else if (element_get_value(e) > element_get_value(curr->element)) 
        curr->right = _avl_insert(curr->right, e);
    
    // Once inserted, we need to verify balancing
    int balancing = _node_get_balance_factor(curr);

    if (balancing < -1 || balancing > 1) 
        return _avl_balance(curr, e, balancing);

    // Else, tree is balanced
    return curr;
}

void avl_insert(AVL *tree, ELEMENT *e) {
    if (tree != NULL) {
        if (tree->root) tree->root = _avl_insert(tree->root, e);
        else tree->root = _node_create(e);
    }
}

static NODE *_avl_remove(NODE **root, int value) {
    if (*root == NULL) return NULL;
    if (value < element_get_value((*root)->element)) 
        (*root)->left = _avl_remove(&(*root)->left, value);
    else if (value > element_get_value((*root)->element))
        (*root)->right = _avl_remove(&(*root)->right, value);
    
    else {
        if (((*root)->left == NULL) || ((*root)->right == NULL)) {
            NODE * tmp = (*root)->left ? (*root)->left : (*root)->right;

            // Without child
            if (tmp == NULL) {
                tmp = (*root);
                (*root) = NULL;
            }
            else  { // only one child
                (*root)->left = tmp->left;
                (*root)->right = tmp->right;
                (*root)->element = tmp->element;
            } 
        }

        else { // both subtree are not empty
            // Finding righter node in left subtree
            NODE *tmp = (*root)->left;
            while (tmp->right != NULL) 
                tmp = tmp->right;

            (*root)->element = tmp->element;
            
            (*root)->left = _avl_remove(&(*root)->left, element_get_value(tmp->element));
        }
    }

    if (*root == NULL) return *root;

    int balancing = _node_get_balance_factor(*root);

    if (balancing > 1 && value < element_get_value((*root)->left->element)) 
        return _right_rotate(*root); // rotate to the right

    else if (balancing < -1 && value >= element_get_value((*root)->left->element))
        return _left_rotate(*root); // rotate to the left
    
    else if (balancing > 1 && value >= element_get_value((*root)->left->element)) 
        return _left_right_rotate(*root); // rotate left then right
        
    else if(balancing < -1 && value < element_get_value((*root)->left->element))
        return _right_left_rotate(*root); // rotate right then left
    
    return *root;
}

void avl_remove(AVL *tree, int value) {
    if (tree == NULL) return;
    tree->root = _avl_remove(&tree->root, value);
}

bool avl_search(AVL *tree, int value) {
	if(tree == NULL)
		return FALSE;
	
    NODE *curr = tree->root;
	while(curr != NULL) {
		if(value == element_get_value(curr->element))
			return TRUE;
		if(value > element_get_value(curr->element))
			curr = curr->right;
		else
			curr = curr->left;
	}

	return FALSE;
}

static void _pre_order(NODE *root) {
    if (root != NULL) {
        printf("%d ", element_get_value(root->element));
        _pre_order(root->left);
        _pre_order(root->right);
    }
}

static void _in_order(NODE *root) {
    if (root != NULL) {
        _in_order(root->left);
        printf("%d ", element_get_value(root->element));
        _in_order(root->right);
    }
}

static void _post_order(NODE *root) {
    if (root != NULL) {
        _post_order(root->left);
        _post_order(root->right);
        printf("%d ", element_get_value(root->element));
    }
}

void avl_print(AVL *tree, int op) {
    if (op == PRE_ORDER) 
        _pre_order(tree->root);
    else if (op == POST_ORDER) 
        _post_order(tree->root);
    else if (op == IN_ORDER) 
        _in_order(tree->root);
    
    printf("\n");
}

static void _avl_destroy(NODE **root) {
    if (*root != NULL) {
        _avl_destroy(&(*root)->left);
        _avl_destroy(&(*root)->right);
        element_delete(&(*root)->element);
        free(*root);
        *root = NULL;
    }   
}

void avl_destroy(AVL **tree) {
    if (tree == NULL) return;
    _avl_destroy(&((*tree)->root));
    
    free(*tree);
    *tree = NULL;
}