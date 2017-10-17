#include "bst.h"

#include <stdbool.h>
#include <stdlib.h>

struct bst_node
{
    void *key;
    void *value;
    struct bst_node *left;
    struct bst_node *right;
};

//----------------------------------------------------------------------------
// Visibility: Public
// 
// Constructor for the Binary Search Tree
//----------------------------------------------------------------------------
bst_type bst_new(void)
{
    bst_type rtn_val = NULL;
    return rtn_val;
}

//----------------------------------------------------------------------------
// Visibility: Private
// 
// Recursive helper function that deletes nodes
//----------------------------------------------------------------------------
static void bst_del_hlp(struct bst_node *node)
{
    if (node != NULL)
    {
        bst_del_hlp(node->left);
        bst_del_hlp(node->right);
        free(node);
    }
}

//----------------------------------------------------------------------------
// Visibility: Public
// 
// Destructor for Binary Search Tree
//----------------------------------------------------------------------------
void bst_del(bst_type *root)
{
    if (*root != NULL)
    {
        bst_del_hlp(*root);
        *root = NULL;
    }
}

//----------------------------------------------------------------------------
// Visibility: Private
// 
// Creates and returns a pointer to a new node populated with key and value.
// Memory for the new node is allocated on the heap
//----------------------------------------------------------------------------
static struct bst_node *bst_new_node(void *key, void *value)
{
    struct bst_node *rtn_node = malloc(sizeof(*rtn_node));

    if (rtn_node != NULL)
    {
        rtn_node->key = key;
        rtn_node->value = value;
        rtn_node->left = NULL;
        rtn_node->right = NULL;
    }

    return rtn_node;
}

//----------------------------------------------------------------------------
// Visibility: Private
// 
// Helper for adding nodes to a Binary Search Tree
//----------------------------------------------------------------------------
static bool bst_add_hlp(struct bst_node **root_ptr,
                        struct bst_node *new_node,
                        bst_cmp_ptype cmp)
{
    // Special case - empty tree
    if (*root_ptr == NULL)
    {
        *root_ptr = new_node;
        return true;
    }

    struct bst_node *curr_node = *root_ptr;

    // Dummy condition, might as well be while (true)
    while (curr_node != NULL)
    {
        int cmp_res = (cmp)(curr_node->key, new_node->key);

        // If key is already in tree, update value and don't do anything else
        if (cmp_res == 0)
        {
            curr_node->value = new_node->value;
            free(new_node);
            return true;
        }

        struct bst_node **side = (cmp_res < 0) ?
                                 &(curr_node->right)
                                 : &(curr_node->left);
        if (*side == NULL)
        {
            *side = new_node;
            return true;
        }

        curr_node = *side;
    }

    // Unreachable
    return false;
}

//----------------------------------------------------------------------------
// Visibility: Public
// 
// Adds a new node to the binary search tree. Comparator has to be provided
// for each call.
//
// Returns true if node has been added or modified; returns false if there
// were issues with memory allocation.
//----------------------------------------------------------------------------
bool bst_add(bst_type *root, void *key, void *value, bst_cmp_ptype cmp)
{
    struct bst_node *new_node = bst_new_node(key, value);

    if (new_node == NULL)
        return false;

    return bst_add_hlp(root, new_node, cmp);
}

//----------------------------------------------------------------------------
// Visibility: Private
// 
// Recursive helper function that prints nodes using given printing function
//----------------------------------------------------------------------------
static void bst_print_hlp(struct bst_node *node,
                          bst_printer_ptype printer)
{
    if (node == NULL)
        return;

    bst_print_hlp(node->left, printer);
    printer(node->key, node->value);
    bst_print_hlp(node->right, printer);
}

//----------------------------------------------------------------------------
// Visibility: Public
// 
// Prints the Binary Search Tree using printer function provided
//----------------------------------------------------------------------------
void bst_print(bst_type *root, bst_printer_ptype printer)
{
    bst_print_hlp(*root, printer);
}

//----------------------------------------------------------------------------
// Visibility: Private
// 
// Search helper function that returns node matching the search key and
// populates pointer to a parent node if it is not NULL
//----------------------------------------------------------------------------
static struct bst_node *bst_search_hlp(struct bst_node *node,
                                       void *key,
                                       bst_cmp_ptype cmp,
                                       struct bst_node **parent)
{
    struct bst_node *local_parent = NULL;
    struct bst_node *curr = node;

    int cmp_res;

    while ((curr != NULL) && ((cmp_res = cmp(curr->key, key)) != 0))
    {
        local_parent = curr;
        curr = (cmp_res < 0) ? curr->right : curr->left;
    }

    if (parent != NULL)
        *parent = local_parent;

    return curr;
}

//----------------------------------------------------------------------------
// Visibility: Public
// 
// Returns value if key is found; returns NULL otherwise
//----------------------------------------------------------------------------
void *bst_search(bst_type *root, void *key, bst_cmp_ptype cmp)
{
    struct bst_node *found_node = bst_search_hlp(*root, key, cmp, NULL);

    return (found_node != NULL) ? found_node->value : NULL;
}


//----------------------------------------------------------------------------
// Visibility: Public
// 
// Deletes a node with key if it exists, else does nothing
//----------------------------------------------------------------------------
void bst_del_node(bst_type *root, void *key, bst_cmp_ptype cmp)
{
    struct bst_node *parent;
    struct bst_node *found_node = bst_search_hlp(*root,
                                                 key,
                                                 cmp,
                                                 &parent);

    if (found_node == NULL)
        return;

    struct bst_node **connection = root;

    if (parent != NULL)
        connection = (parent->left == found_node) ?
                     &(parent->left)
                     : &(parent->right);

    if (found_node->left == NULL)
    {
        *connection = found_node->right;
        free(found_node);
        return;
    }

    *connection = found_node->left;

    if (found_node->right != NULL)
    {
        bst_add_hlp(connection, found_node->right, cmp);
    }

    free(found_node);
}
