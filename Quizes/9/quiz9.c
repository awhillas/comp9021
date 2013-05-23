/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       reorder.c                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "reorder.h"
#include "tailored_list.h"

void print_list(const Node *const);
void print_node(const int);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Provide some characters (at least one) as command-line arguments.\n");
        return EXIT_FAILURE;
    }
    Node *list = NULL;
    for (int i = 1; i < argc; ++i)
        append_to_list(argv[i][0], &list);
    reorder(&list);
    print_list(list);
    return EXIT_SUCCESS;
}

void print_list(const Node *const pt_to_node) {
    if (!pt_to_node)
        printf("()\n");
    else {
        printf("(");
        apply_to_list(print_node, pt_to_node);
        printf("\b)\n");
    }
}

void print_node(const int value) {
    printf("%c,", value);
}  

