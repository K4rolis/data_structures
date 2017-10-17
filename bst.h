#ifndef BST_H
#define BST_H

#include <stdbool.h>
// Type definition
typedef struct bst_node *bst_type;
typedef int (*bst_cmp_ptype)(const void *, const void *);
typedef void (*bst_printer_ptype)(const void *, const void *);

// Constructor
bst_type bst_new(void);

// Destructor
void bst_del(bst_type *root);

// Print the BST
void bst_print(bst_type *root, bst_printer_ptype printer);

// Add a node to the BST
bool bst_add(bst_type *root, void *key, void *value, bst_cmp_ptype cmp);

// Delete a node with matching key from the BST
void bst_del_node(bst_type *root, void *key, bst_cmp_ptype cmp);

// Search for a node with key - returns the the value
void *bst_search(bst_type *root, void *key, bst_cmp_ptype cmp);

#endif /* !BST_H */
