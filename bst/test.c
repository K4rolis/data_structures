#include <string.h>
#include <stdio.h>

#include "bst.h"

void print_vals(const void *key, const void *value)
{
    char *key_str = (char *)key;
    char *value_str = (char *)value;

    printf("%s: %s\n", key_str, value_str);
}

int main(void)
{
    bst_type bst;

    bst = bst_new();

    bst_print(&bst, print_vals);
    puts("---");
    bst_add(&bst, "f", "hello", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");
    bst_add(&bst, "g", "world", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");
    bst_add(&bst, "e", "say", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");
    bst_add(&bst, "a", "I", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");

    printf("Value of node with key %s: %s\n", "g",
                                              (char *)bst_search(&bst,
                                                                 "g",
                                                                 (bst_cmp_ptype)strcmp));
    printf("Value of node with key %s: %s\n", "x",
                                              (char *)bst_search(&bst,
                                                                 "x",
                                                                 (bst_cmp_ptype)strcmp));
    puts("---");
    bst_del_node(&bst, "f", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");

    bst_del_node(&bst, "a", (bst_cmp_ptype)strcmp);
    bst_print(&bst, print_vals);
    puts("---");

    bst_del(&bst);

    return 0;
}

