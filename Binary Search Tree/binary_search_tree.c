#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct _node {
    NODE *left;
    NODE *right;
    ELEMENT *element;
};

struct _bst {
    NODE *root;
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(1 * sizeof(NODE));
    new_node->element = e;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

BST *bst_create(void) {
	BST *tree = malloc(1 * sizeof(BST));
	
	if(tree != NULL) 
        tree->root = NULL;
	
	return tree;
}

static NODE *_bst_insert_rec(NODE *root, ELEMENT *e) {
    if (root == NULL) {
        root = _node_create(e);
    } else if (element_get_value(e) > element_get_value(root->element)) {
        root->right = _bst_insert_rec(root->right, e);
    } else if (element_get_value(e) < element_get_value(root->element)) {
        root->left = _bst_insert_rec(root->left, e);
    }

    return root;
}

static bool _bst_insert_iter(BST *tree, ELEMENT *e) {
    if (tree == NULL) return FALSE;

    NODE *new_node = _node_create(e);

    if (tree->root == NULL) tree->root = new_node;
    
    else {
        NODE *curr = tree->root;
        NODE *prev = NULL;

        while (curr != NULL) {
            prev = curr;
            
            if (element_get_value(e) == element_get_value(curr->element)) {
                free(new_node);
                return FALSE; // Value already exist in bst 
            }

            if (element_get_value(e) > element_get_value(curr->element)) 
                curr = curr->right;
            else 
                curr = curr->left;
        }

        if (element_get_value(e) > element_get_value(prev->element))
            prev->right = new_node;
        else 
            prev->left = new_node;
    }

    return TRUE;
}

bool bst_insert(BST *tree, ELEMENT *e, int op) {
    if (op == ITERATIVE) return (tree->root = _bst_insert_rec(tree->root, e)) != NULL;
    return _bst_insert_iter(tree, e); 
}


static bool _bst_delete(NODE **root, int value) {

    // First case: empty tree
    if ((*root) == NULL) return FALSE;

    // Searching node in tree
    else if (element_get_value((*root)->element) > value)
        return _bst_delete(&(*root)->left, value);

    else if (element_get_value((*root)->element) < value)
        return _bst_delete(&(*root)->right, value);

    // Once we found the element
    else {
        // Leaf node
        if((*root)->left == NULL && (*root)->right == NULL) {
            free((*root));
            (*root) = NULL;
            return TRUE;
        }

        // Has right child
        else if ((*root)->left == NULL) {
            NODE *trade = (*root);
            (*root) = (*root)->right;
            free(trade);
            trade = NULL;

            return TRUE;
        }
        
        // Has left child
        else if ((*root)->right == NULL) {
            NODE *trade = (*root);
            (*root) = (*root)->left;
            free(trade);
            trade = NULL;

            return TRUE;
        }

        // Has both subtrees
        else { 
            // Finding righter node in left subtree
            NODE *trade = (*root)->left;
            while (trade->right != NULL) 
                trade = trade->right;
            
            // Trading data
            (*root)->element = trade->element;

            // Removing value we first wanted to remove
            return _bst_delete(&(*root)->left, element_get_value(trade->element));
        }
    }
}

bool bst_delete(BST *tree, int value) {
    return _bst_delete(&tree->root, value);
}

bool bst_search(BST *tree, int value) {
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

void bst_print(BST *tree, int op) {
    if (op == PRE_ORDER) 
        _pre_order(tree->root);
    else if (op == POST_ORDER) 
        _post_order(tree->root);
    else if (op == IN_ORDER) 
        _in_order(tree->root);
    
    printf("\n");
}

static void _bst_destroy(NODE **root) {
    if (*root != NULL) {
        _bst_destroy(&(*root)->left);
        _bst_destroy(&(*root)->right);
        element_delete(&(*root)->element);
        free(*root);
        *root = NULL;
    }   
}

void bst_destroy(BST **tree) {
    if (tree == NULL) return;
    _bst_destroy(&((*tree)->root));
    
    free(*tree);
    *tree = NULL;
}